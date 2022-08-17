using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public GameObject player;

    private Vector3 offset;//offset distance between player and camera

    public float perspectiveZoomSpeed = .5f;

    public float orthoZoomSpeed = .5f;

    // Start is called before the first frame update
    void Start()
    {
        offset = transform.position - player.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        float deltaMagnitudeDiff = 0.0f;
        //to avoid input conflict, pinch zoom is triggered when touch count is 3, not 2!
        if (Input.touchCount == 3)
        {//zoom based on 2 finger's touch positions
            Touch touchZero = Input.GetTouch(0);
            Touch touchOne = Input.GetTouch(1);
            Vector2 TouchZeroPrevPos =
                touchZero.position - touchZero.deltaPosition;
            Vector2 TouchOnePrevPos =
                touchOne.position - touchOne.deltaPosition;
            //compare previouos touch position with current touch position
            //to determine the magnitude of zooming
            float PrevTouchDeltaMag =
                (TouchZeroPrevPos - TouchOnePrevPos).magnitude;
            float TouchDeltaMag =
                (touchZero.position - touchOne.position).magnitude;

            deltaMagnitudeDiff = PrevTouchDeltaMag - TouchDeltaMag;
            ZoomFunc (deltaMagnitudeDiff);
        }
        else if (Mathf.Abs(Input.mouseScrollDelta.y) >= 0.0001f)
        {//PC mouse scroll
            deltaMagnitudeDiff = Input.mouseScrollDelta.y;
            ZoomFunc (deltaMagnitudeDiff);
        }
    }

    void ZoomFunc(float diff)
    {//Clamp the field of view so zoomming won't make the view look too ridiculous
        if (Camera.main.orthographic)
        {
            Camera.main.orthographicSize += diff * orthoZoomSpeed;
            Camera.main.orthographicSize =
                Mathf.Max(Camera.main.orthographicSize, .1f);
        }
        else
        {
            Camera.main.fieldOfView += diff * perspectiveZoomSpeed;
            Camera.main.fieldOfView =
                Mathf.Clamp(Camera.main.fieldOfView, .1f, 179.9f);
        }
    }
    
    // Update is called once per frame
    void LateUpdate()
    {//update camera position based on player position, plus offset
        transform.position = player.transform.position + offset;
    }
}
