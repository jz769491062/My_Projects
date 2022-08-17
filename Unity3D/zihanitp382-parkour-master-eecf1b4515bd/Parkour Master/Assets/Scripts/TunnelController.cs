using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TunnelController : MonoBehaviour
{
    Vector3 startPosition, tempPosition;//tempposition to store position during the move
    bool goingRight = true;//Are we going right?
    public float tunnelSpeed;//horizontal moving speed for the tunnel
    float displaced = 0.0f;//how much dispaced from original point
    float displaceMaxPos = 10.0f;//max x pos to reach
    float displaceMinPos = -20.0f;//min x pos to reach
    void Start()
    {
        //get start position as reference
        startPosition = transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        MoveLeftAndRight(Time.fixedDeltaTime);
    }

    //Move the object left and right
    void MoveLeftAndRight(float dT)
    {
        tempPosition = transform.position;
        if(goingRight)
        {//if going right, decrease x value
            tempPosition.x -= dT*tunnelSpeed;
            displaced -= dT*tunnelSpeed;
            transform.position = tempPosition;
            //reached the min point, move left instead
            if(tempPosition.x < displaceMinPos)
            {
                goingRight = false;
            }
        }
        else
        {//going left, increase x value
            tempPosition.x += dT*tunnelSpeed;
            displaced += dT*tunnelSpeed;
            transform.position = tempPosition;
            //reached max point, move right instead
            if(tempPosition.x > displaceMaxPos)
            {
                goingRight = true;
            }
        }
    }
}
