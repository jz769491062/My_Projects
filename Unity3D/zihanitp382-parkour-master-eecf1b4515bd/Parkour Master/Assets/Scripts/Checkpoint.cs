using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Checkpoint : MonoBehaviour
{
    public AudioSource cpaudio;
    // Start is called before the first frame update
    void Start()
    {

    }

    void OnTriggerEnter(Collider c)
    {
        //after colliding with player, play sound, destroy self
        if(c.gameObject.tag == "Player")
        {
            this.cpaudio.Play();
            this.gameObject.SetActive(false);
        }
    }
}
