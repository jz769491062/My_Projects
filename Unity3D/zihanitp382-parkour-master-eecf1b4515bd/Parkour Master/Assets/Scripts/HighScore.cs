using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class HighScore : MonoBehaviour
{   
    int highScore;//high score of current level
    string currLevelString;//"1" or "2" or "3", used to simplify code
    void Start()
    {
        highScore = 0;
        currLevelString = "";
        //based on current scene, read corresponding playerpref data to get highscore
        Scene s = SceneManager.GetActiveScene();
        if(s.name == "Level1Scene")
        {
            currLevelString = "1";
        }
        else if(s.name == "Level2Scene")
        {
            currLevelString = "2";
        }
        else if(s.name == "Level3Scene")
        {
            currLevelString = "3";
        }
        if (PlayerPrefs.HasKey("HighScore"+currLevelString))
        {
            highScore = PlayerPrefs.GetInt("HighScore"+currLevelString);
        }
        //update high score text
        Text gt = this.GetComponent<Text>();
        gt.text = "High Score: " + highScore;
    }

    public void checkHighScore(int sc)
    {//called at the end of the level, check if should update high score
        //is the new score higher than the previously recorded highscore?
        if (sc > highScore)
        {
            //update highscore
            highScore = sc;
            // Update the PlayerPrefs HighScore if necessary
            if (highScore > PlayerPrefs.GetInt("HighScore"+currLevelString))
            {
                PlayerPrefs.SetInt("HighScore"+currLevelString, highScore);
            }
            //update highscore text now
            Text gt = this.GetComponent<Text>();
            gt.text = "High Score: " + highScore;
        }
    }
}
