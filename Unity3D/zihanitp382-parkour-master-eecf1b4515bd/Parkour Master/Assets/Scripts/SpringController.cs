using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpringController : MonoBehaviour
{
    Vector3 startPosition, tempPosition;//tempposition to store position during the move
    bool goingDown = true;//are we going down?
    public float springSpeed = 2.0f;//speed for the spring motion
    float displaced = 0.0f;//how much dispaced from original point
    float displaceMaxDistance = 0.5f; //max y distance to displace up/down
    // Start is called before the first frame update
    void Start()
    {
        //get start position as reference
        startPosition = transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        MoveUpAndDown(Time.fixedDeltaTime);
    }

    //Move the Spring object up and down
    void MoveUpAndDown(float dT)
    {
        tempPosition = transform.position;
        if(goingDown)
        {//going down, decrease y value
            tempPosition.y -= dT*springSpeed;
            displaced -= dT*springSpeed;
            transform.position = tempPosition;
            //displaced enough, now move up
            if(displaced < -displaceMaxDistance)
            {
                goingDown = false;
            }
        }
        else
        {//going up, increase y value
            tempPosition.y += dT*springSpeed;
            displaced += dT*springSpeed;
            transform.position = tempPosition;
            //displaced enough, now move down
            if(displaced > displaceMaxDistance)
            {
                goingDown = true;
            }
        }
    }
}
