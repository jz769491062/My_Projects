using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Player : MonoBehaviour
{
    private Rigidbody rb;//player's rigidbody
    public float moveSpeed;//player move speed
    public float gravityVal;//gravity value for the player
    public float climbSpeed;//climb speed for the player
     public float climbCountdownValue;//maximum time player can climb
    public Joystick Joystick;
    public Text scoreText;//shows current score
    public GameObject jumpButtonObject;//jump button
    private int score;
    public Text winText;//prompt text at the top center
    public Button restartButton;
    public Button menuButton;
    public GameObject nextLevelButtonObject;//next level button
    public GameObject highScoreObject;//highscore object, used to locate highscore script
    private HighScore hsScript;//highscore script, call checkHighScore() function to update highscore
    private float movementX;//keyboard movement x
    private float movementY;//keyboard movement y
    private float textCountdown;// how long should a new piece of text be displayed
    private float climbCountdown;//current climb countdown timer
    private float scoreCountdown;//score countdown, keep decreasing scores to motivate speedrunning
    private bool textCountdownStart;//has text countdown started?
    private bool onGround;//make sure player can jump only on ground, not jumping infinitely
    private bool climbing;//is the player climbing?
    //audio sources for climbing, falling, and bomb exploding
    public AudioSource climbAudio;
    public AudioSource fallAudio;
    public AudioSource bombAudio;


    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        //jump button listener
        Button btn = jumpButtonObject.GetComponent<Button>();
        btn.onClick.AddListener (DoJump);
        //prompt message
        winText.text = "Use Joystick to move, tap the jump button to jump, jump towards the wall to climb";
        //restart, next, and menu button listeners
        restartButton.onClick.AddListener(RestartCurrGame);
        menuButton.onClick.AddListener(ReturnToMenu);
        Button btnNext = nextLevelButtonObject.GetComponent<Button>();
        btnNext.onClick.AddListener(loadNextLevel);
        //hide next button until player wins a level
        nextLevelButtonObject.SetActive(false);
        //initial score: 20, decrease by 1 per second
        score = 20;
        SetScoreText();//set score text
        textCountdown = 3.0f;//text show for 3 seconds
        scoreCountdown = 1.0f;//score decrease by 1 per second
        textCountdownStart = false;
        onGround = true;
        climbing = false;
        climbCountdown = climbCountdownValue;
        Physics.gravity = new Vector3(0, gravityVal, 0);//update gravity now
        highScoreObject = GameObject.Find("HighScoreText");
        //find Highscore script to update level 1-3 highscores. Tutorial level has no highscores.
        if(highScoreObject)
        {
            hsScript = highScoreObject.GetComponent<HighScore>();
        }
    }

    void DoJump()
    {//can jump only when on ground
        if (onGround)
        {
            rb.AddForce(new Vector3(0.0f, 15.0f, 0.0f), ForceMode.VelocityChange);
            onGround = false;
        }
    }

    void UpdateClimbStuff(float dT)
    {
        climbCountdown -= dT;
        if(climbCountdown < 0.0f)
        {
            climbCountdown = climbCountdownValue;
            climbing = false;
            climbAudio.Stop();
        }
        rb.AddForce(new Vector3(0.0f, climbSpeed * dT, 0.0f));
    }

    void FixedUpdate()
    {   //decrease score by 1 per second
        scoreCountdown -= Time.fixedDeltaTime;
        if(scoreCountdown < 0.0f)
        {
            scoreCountdown = 1.0f;
            score -= 1;
            SetScoreText();
        }
       
        //joystick part
        Vector3 direction = Vector3.forward * Joystick.Vertical + Vector3.right * Joystick.Horizontal;
        //If climbing, when player goes forward we actually make player go up
        if(climbing)
        {
            if(Mathf.Abs(Joystick.Vertical) > Mathf.Abs(Joystick.Horizontal))
            {
                if(Joystick.Vertical < 0.0f)
                {
                    direction = Vector3.up * -Joystick.Vertical + Vector3.right * Joystick.Horizontal;
                }
                else
                {
                    direction = Vector3.up * Joystick.Vertical + Vector3.right * Joystick.Horizontal;
                }
            }
            else
            {
                if(Joystick.Horizontal < 0.0f)
                {
                    direction = Vector3.forward * Joystick.Vertical + Vector3.up * -Joystick.Horizontal;
                }
                else
                {
                    direction = Vector3.forward * Joystick.Vertical + Vector3.up * Joystick.Horizontal;
                }
            }
            //update climb countdown and climb force and audio
            UpdateClimbStuff(Time.fixedDeltaTime);
        }
        //add force after calculating the direction
        rb.AddForce(direction * moveSpeed * Time.fixedDeltaTime, ForceMode.VelocityChange);

        //keyboard part
        Vector3 movement = new Vector3(movementX, 0.0f, movementY);
        //climbing?
        if(climbing)
        {
            if(Mathf.Abs(movementX) > Mathf.Abs(movementY))
            {
                if(movementX < 0.0f)
                {
                    movement = new Vector3(0.0f, -movementX, movementY);
                }
                else
                {
                    movement = new Vector3(0.0f, movementX, movementY);
                }
            }
            else
            {
                if(movementY < 0.0f)
                {
                    movement = new Vector3(movementX, -movementY, 0.0f);
                }
                else
                {
                    movement = new Vector3(movementX, movementY, 0.0f);
                }
            }
            //update climb countdown and climb force and audio
            UpdateClimbStuff(Time.fixedDeltaTime);
        }
        //add force after calculating the direction
        rb.AddForce(movement * moveSpeed * Time.fixedDeltaTime, ForceMode.VelocityChange);

        //player respawn after falling off
        if (rb.position.y < -30.0f)
        {
            rb.position = new Vector3(0f, 2f, -35.0f);
            rb.velocity = Vector3.zero;

            //also need to set angular velocity to 0 to completely stop player motion after respawn
            rb.angularVelocity = Vector3.zero;

            //decrease score by 10. If score too low, destroy player, call fail
            score = score - 10;
            SetScoreText();
            winText.text = "You fell off. Be careful!";
            textCountdownStart = true;
            fallAudio.Play();
        }
        //if score is negative, game lost
        if (score <= -1)
        {
            winText.text = "You lost! Click restart button to play again.";
            this.gameObject.SetActive(false);
        }

        //Are we doing text display countdowns?
        if (textCountdownStart)
        {   //if yes, show prompt text for 3 seconds first
            textCountdown -= Time.fixedDeltaTime;
            if (textCountdown <= 0.0f)
            {
                winText.text = "Use Joystick to move, tap the jump button to jump, jump towards the wall to climb";
                textCountdown = 3.0f;
                textCountdownStart = false;
            }
        }
    }

    void OnMove(InputValue value)
    {
        Vector2 v = value.Get<Vector2>();
        movementX = v.x;
        movementY = v.y;
    }

    void OnTriggerEnter(Collider other)
    {
        //Each collectible +10
        if (other.gameObject.CompareTag("Collectible"))
        {
            score = score + 10;
            SetScoreText();
        }
        else if (other.gameObject.CompareTag("Checkpoint"))
        {//reached checkpoint, update highscore, prompt text, and show next level button
            if(hsScript)
            {
                hsScript.checkHighScore (score);
            }
            winText.text = "You win! Your Score is: " + score + "\nYou can proceed to the next level or return.";
            this.gameObject.SetActive(false);
            Scene s = SceneManager.GetActiveScene();//get current active scene, used for switching scenes
            if(s.name != "Level3Scene")
            {
                nextLevelButtonObject.SetActive(true);
            }
            
        }
        else if (other.gameObject.CompareTag("Spring"))
        {//springs bring the player up
            rb.AddForce(new Vector3(0.0f, 35.0f, 0.0f), ForceMode.VelocityChange);
            //this text should only show for 3 seconds
            winText.text = "You've triggered a spring";
            textCountdownStart = true;
            onGround = false;
        }
        else if (other.gameObject.CompareTag("Bomb"))
        {//bomb brings the player very high to make them fall and waste their time
            rb.AddForce(new Vector3(0.0f, 300.0f, 0.0f), ForceMode.VelocityChange);
            //this text should only show for 3 seconds
            winText.text = "BOOOOOOOOOOM!";
            bombAudio.Play();
            textCountdownStart = true;
            onGround = false;
        }
    }

    void OnCollisionEnter(Collision collision)
    {//if reached plane, we are on ground and can jumb. Not climbing any more
        if (collision.gameObject.tag == "Plane")
        {
            onGround = true;
            climbing = false;
            climbCountdown = climbCountdownValue;
            climbAudio.Stop();
        }
        if (collision.gameObject.tag == "Wall")
        {
                //collision contact point
                ContactPoint contact = collision.contacts[0];
                //Are we moving towards the wall, and not on the ground, and fast enough?
                //if yes, we start climbing
                //would need to jump and run to achieve enough speed
                if (!climbing  && !onGround && rb.velocity.magnitude > 4 &&
                Mathf.Abs(Vector3.Dot(Vector3.Normalize(rb.velocity), Vector3.Normalize(contact.point - transform.position))) < 0.3f )
                {
                    climbing = true;
                    climbAudio.Play();
                }
        }
        
    }

    void SetScoreText()
    {
        scoreText.text = "Score: " + score.ToString();
    }

    void RestartCurrGame()
    {//restart button functionality, reload current scene
        Scene s = SceneManager.GetActiveScene();
        SceneManager.LoadScene(s.name);
    }
    
    void ReturnToMenu()
    {
        SceneManager.LoadScene("MenuScene");
    }

    void loadNextLevel()
    {
        Scene s = SceneManager.GetActiveScene();//get current active scene, used for switching scenes
        if(s.name == "TutorialScene")
        {
            SceneManager.LoadScene("Level1Scene");
        }
        else if(s.name == "Level1Scene")
        {
            SceneManager.LoadScene("Level2Scene");
        }
        else if(s.name == "Level2Scene")
        {
            SceneManager.LoadScene("Level3Scene");
        }
    }
}


