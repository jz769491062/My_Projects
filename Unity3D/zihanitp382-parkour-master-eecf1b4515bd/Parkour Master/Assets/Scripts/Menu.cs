using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Menu : MonoBehaviour
{
    public Button tutorialButton, level1Button, level2Button, level3Button;
    public Text level1Text, level2Text, level3Text;
    // Start is called before the first frame update
    void Start()
    {
        //add listeners to load the corresponding levels when level buttons are clicked
        tutorialButton.onClick.AddListener (loadTutorial);
        level1Button.onClick.AddListener (loadLevel1);
        level2Button.onClick.AddListener (loadLevel2);
        level3Button.onClick.AddListener (loadLevel3);
        //load from player preference to fetch the high score record
        if (PlayerPrefs.HasKey("HighScore1"))
        {
            level1Text.text = "Level 1 Highscore: " + PlayerPrefs.GetInt("HighScore1");
        }
        if (PlayerPrefs.HasKey("HighScore2"))
        {
            level2Text.text = "Level 2 Highscore: " + PlayerPrefs.GetInt("HighScore2");
        }
        if (PlayerPrefs.HasKey("HighScore3"))
        {
            level3Text.text = "Level 3 Highscore: " + PlayerPrefs.GetInt("HighScore3");
        }
    }

    void loadTutorial()
    {
        SceneManager.LoadScene("TutorialScene");
    }

    void loadLevel1()
    {
        SceneManager.LoadScene("Level1Scene");
    }

    void loadLevel2()
    {
        SceneManager.LoadScene("Level2Scene");
    }

    void loadLevel3()
    {
        SceneManager.LoadScene("Level3Scene");
    }
}
