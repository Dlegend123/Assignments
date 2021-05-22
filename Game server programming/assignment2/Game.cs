using System;
using System.Collections.Generic;

namespace assignment2
{
    public class Game<T> where T : IPlayer
    {
        private List<T> _players;

        public Game(List<T> players)
        {
            _players = players;
        }

        public T[] GetTop10Players()
        {
            int[] highScores = new int[10];

            for(int i = 0; i < 10; i++)
            {
                highScores[i] = _players[i].Score;
            }
            int[] temp = highScores;
            for (int i = 1; i <= 9; i++)
            {
                for (int j = 1; j <= 9 - 1; j++)
                {
                    if (highScores[j] > highScores[j + 1])
                    {
                        int x = highScores[j];
                        highScores[j] = highScores[j + 1];
                        highScores[j + 1] = x;
                    }
                }
            }

                for (int i = 1; i <= _players.Count; i++)
                {
                    for (int j = 1; j <= _players.Count - 1-1; j++)
                    {
                        if (_players[j].Score > _players[j + 1].Score)
                        {
                            int x = _players[j].Score;
                            _players[j].Score = _players[j + 1].Score;
                            _players[j + 1].Score = x;
                        }
                    }
                }
            int r = 0;
            T[] topPlayers = new T[10];
            for (int i = _players.Count-1; i >= _players.Count - 10; i--) {
                topPlayers[r] = _players[i];
                r++;
            }
            // ... write code that returns 10 players with highest scores
            return topPlayers;
        }
    }
}
