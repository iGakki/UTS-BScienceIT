#ifndef _PLAYER_H
#define _PLAYER_H

enum PlayerNum
{
    NOPLAYER = 0,
    PLAYER1 = 1,
    PLAYER2 = 2
};

// object for managing players

class Player
{
    private:
        PlayerNum player;
       
    public:
        // constructors
        Player() : player(NOPLAYER)
        {
        }
       
        Player(PlayerNum pn) : player(pn)
        {
        }
        
        Player(const Player &other) : player(other.player)
        {
        }
       
        // set and get player
        void setPlayer(PlayerNum pn)
        {
            player = pn;
        }
        
        void setPlayer(const Player &other)
        {
            player = other.player;
        }
        
        void swapPlayer()
        {
            // make the player equal to the other player
            player = otherPlayer(player);
        }
        
        PlayerNum getPlayer() { return player; }
        
        // static methods
        static PlayerNum otherPlayer(PlayerNum aPlayer)
        {
            // return who opponent is to a particular player
            if (aPlayer == PLAYER1) return PLAYER2;
            else if (aPlayer == PLAYER2) return PLAYER1;
            else return aPlayer;
        }
        
        static PlayerNum otherPlayer(const Player &aPlayer)
        {
            return otherPlayer(aPlayer.player);
        }  

		PlayerNum otherPlayer()
		{
		    return otherPlayer(player);
		}
        
        // overloaded operators
        const Player& operator = (const Player &other)
        {
            player = other.player;
            return *this;
        }
        
        const Player& operator = (PlayerNum other)
        {
            player = other;
            return *this;
        }
        
        bool operator == (const Player &other) const
        {
            return (player == other.player);
        }
        
        bool operator == (PlayerNum pn) const
        {
            return (player == pn);
        }
};

#endif

