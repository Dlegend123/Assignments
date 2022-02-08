#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <queue>
using namespace std;

int nFlasks = 50; //The number of flasks in the barrel starts at 50
int sLeft = 0;
int wCount = 0;
sem_t sSem, bSem; // declaring semaphores
queue<int> dropOff;

// function prototype
void *bartender(void *);             // the prototype of the bartender thread function
void *student(void *);               // the prototype of the student thread function
int get_serving(int, int, int);      //the prototype for the get serving function
void refill_barrel(int, int);        // the prototype for the refilling function
void drink_and_think(int, int, int); // the prototype for the drinking and thinking function

class ThreadParam{// a set of parameters to be passed to each thread
  public:
    ThreadParam(int tId, int pId, int value) : tId(tId), pId(pId), value(value) {}
    int tId; // a thread identifier
    int pId; //a process identifier
    int value;
};

void refill_barrel(int pId, int tId) { //Refills barrel if wake count is less than 3 and if the barrel is empty

    if (wCount < 3)
    {
        if (nFlasks == 0)
        {
            sleep(3); //Gives another process's thread a chance to output information at a different time
            cout << "\nProcess ID: " << pId << endl;
            cout << "Process Type: Bartender\n";
            cout << "Thread ID: " << tId << endl;

            cout << "Wake Count: " << ++wCount << endl; //Increments the wake count then displays it
            cout << "Thread State: Refilling\n";

            sleep(8); //Refill time is 8 seconds

            srand(time(0));            //Attempts to make the random number different each time
            sem_wait(&bSem);           // acquire a lock
            //start the bartender critical section
            nFlasks = 1 + rand() % 50; //Assigns a random number to the number of flasks in the barrel
            //Leave the critical section.
            sem_post(&bSem); // release semaphore
        }
    }
}

int get_serving(int nBeers, int tId, int pId) { //get_serving function

    cout << "\nProcess ID: " << pId << endl;//Displays the process ID
    cout << "Process Type: Student";        //Displays the process type
    cout << "\nThread ID: " << tId << endl; //displays the thread ID
    cout << "Thread State: Waiting";        //Displays thread state
    cout << "\nLight beer required: " << nBeers << endl;
    sem_wait(&sSem); // acquire a lock
    //start the student critical section

    if (nFlasks < nBeers) {
        if (wCount >= 3) {
            dropOff.push(tId);

            if (nFlasks > 0) {
                nBeers -= nFlasks;
                nFlasks = 0;
            }
            else
                nBeers = 0;
        }
        else {
            int num = nBeers;

            while (nFlasks < num && wCount != 3) {

                num -= nFlasks;
                nFlasks -= nFlasks;//Makes the value in nFlasks equal to zero to meet the refill condition
                sleep(12);// Waits until bartender refills barrel

            }
            if (num > 0) {
                nBeers -= num;
                dropOff.push(tId);

                if (nFlasks > 0) {
                    nBeers -= nFlasks;
                    nFlasks = 0;
                }
            }
        }
    }
    else
        nFlasks -= nBeers;

    sleep(5); //The waiting time is 5 seconds

    //Leave the critical section.
    sem_post(&sSem); // release semaphore
    return nBeers;
}

void drink_and_think(int tId, int nBeers, int pId) { //Student drinks and thinks

    sleep(2); //Gives another process's thread a chance to output information at a different time
    cout << "\nProcess ID: " << pId << endl;  //Displays the process ID
    cout << "Process Type: Student\n";  //Displays the process type
    cout << "Thread ID: " << tId << "\nThread State: Drinking-Thinking\n"; //displays the thread ID and thread state
    cout << "Light beer Consumption: " << nBeers << endl; //displays the number of beers consumed
    sleep(7);  //Drinking and thinking time is 7 seconds
}

void* bartender(void* arg) {// the bartender thread function
    // extract parameters
    ThreadParam& param = *(ThreadParam*)arg;

    int tId = param.tId;
    int pId = param.pId;
    delete& param;

    while (true) {// keep working until being terminated by the main
        refill_barrel(pId, tId); // refill barrel

        if (sLeft == 0 || wCount == 3) { //Terminates bartender thread if all thw students have been served or if the bartender wakes uo three times
            cout << "\nProcess ID: " << pId << endl;    //Displays the process ID
            cout << "Process Type: Bartender";  //Displays the process type
            cout << "\nThread ID: " << tId << "\nThread State: Terminated\n"; //displays the thread ID and thread state
            pthread_exit(NULL); //terminates thread
        }
    }
    return 0;
}

void* student(void* arg) {// the student thread function
    // extract parameters
    ThreadParam& param = *(ThreadParam*)arg;
    int tId = param.tId;
    int pId = param.pId;
    int value = param.value;
    delete& param;

    while (true) { // keep working until terminated

        value = get_serving(value, tId, pId); //Let student collect beers
        drink_and_think(tId, value, pId);     //lets student drink and think
        cout << "\nProcess ID: " << pId << endl;
        cout << "Process Type: Student";
        cout << "\nThread ID: " << tId << "\nThread State: Terminated\n";
        sLeft--;
        pthread_exit(NULL); //terminates a student thread
    }
    return 0;
}

void invalidInput() { //Helps with input validation

    cin.clear();
    cin.ignore();
    system("clear");
    cout << "Invalid Choice, only whole numbers >=1 should be entered\n";
}

int main() {

    float temp = 0;
    int nStudents = 1;          // initializes the nStudents variable
    pthread_t bartender_thread; //declares the bartender thread
    pthread_t* student_threads; //declares a pointer for student threads
    void* status;
    int* nBeers = NULL;

    if (sem_init(&sSem, 0, 1) != 0) { //initializes  and check if the semaphore was initialized

        printf("\n semaphore initialization has failed\n");

        return 1;
    }

    if (sem_init(&bSem, 0, 1) != 0){ //initializes  and check if the semaphore was initialized

        printf("\n semaphore initialization has failed\n");

        return 1;
    }

    cout << "Enter the number of students: ";

    cin >> temp; //accept the # of students that want light beers

    while (cin.fail() || (temp < 0 || (temp - (int)temp) > 0)) {
        invalidInput();
        cout << "Enter the number of students: ";
        cin >> temp; // accepts the number of students that want to be served
    }

    nStudents = temp;
    nBeers = new int[nStudents];
    sLeft = nStudents;

    for (int i = 0; i < nStudents; i++) { //Obtain the number of beers required for each student

        cout << "\nStudent " << i + 1 << " how many beers do you require ? ";
        cin >> temp;

        while (cin.fail() || (temp < 0 || (temp - (int)temp) > 0)) { //checks for error in input and validates input

            invalidInput();
            cout << "\nStudent " << i + 1 << " how many beers do you require ? ";
            cin >> temp;
        }
        nBeers[i] = temp;

        while (nBeers[i] > 50 || nBeers[i] < 1) { //Validates the number of beers entered

            system("clear");
            cout << "The number must be >=1 and <=50\n";
            cout << "\nStudent " << i + 1 << " how many beers do you require ? ";
            cin >> temp;

            while (cin.fail() || (temp < 0 || (temp - (int)temp) > 0)) {
                invalidInput();
                cout << "\nStudent " << i + 1 << " how many beers do you require ? ";
                cin >> temp;
            }
            nBeers[i] = temp;
        }
    }

    system("clear"); //clears the screen
    student_threads = new pthread_t[nStudents];

    ThreadParam* param = new ThreadParam(1, getpid() + 1, 0);
    int rc;
    pthread_create(&bartender_thread, NULL, bartender, (void*)param); //instantiate bartender

    for (int i = 0; i < nStudents; i++) { // instantiate students

        ThreadParam* param = new ThreadParam(i + 1, getpid() + 2, nBeers[i]);

        rc = pthread_create(&student_threads[i], NULL, student, (void*)param);
        sleep(3);
        if (rc)
            cout << "Error:unable to create thread," << rc << endl;
    }

    for (int i = 0; i < nStudents; i++) { // wait until all the students are served

        rc = pthread_join(student_threads[i], &status);

        if (rc) {
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }
    }

    while (!dropOff.empty()) {
        cout << "\nUnable to fulfill request of Student " << dropOff.front(); //Displays the students that couldnt get all the beers they required
        dropOff.pop();
    }

    cout << endl;

    sem_destroy(&sSem);     //destroy semaphore lock
    sem_destroy(&bSem);     //destroy semaphore lock
    delete student_threads; //destroy student thread pointer
    delete nBeers;          //destroy pointer to number of beers

    return 0;
}
