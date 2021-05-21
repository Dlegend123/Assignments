//Card.h
#ifndef CARD_H
#define CARD_H

class Card{
	
  private:
  
	string type;
	string value;

  public:
  
	Card(){//initializes the attributes of the class
		type = "Card";
		value.assign("0");
	}

	void setType(int i){//Figure out and sets the type
		if (i == 23 || i==13 || i==8 || i==17 || i==1)
			type = (i == 23 ||i== 13|| i==8) ? "BANKRUPTCY" : "LOSE A TURN";
		else
			type = "MONEY";
	}
	
	void setValue(string option[], int i){//figures out and sets the value
		if (i == 23 || i==13 || i==8 || i==1 ||i== 15 || i==1){
			if (i == 15)
				value.assign("850");
		}
		else
			value = option[i];
	}
	
	float getValue(){//returns the value
		return stof(value);
	}
	
	string getType(){//returns the type
		return type;
	}
	
	~Card(){
	}
};
#endif