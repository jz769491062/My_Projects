using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollectibleController : MonoBehaviour
{
    public AudioSource collectibleAudio;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {//Collectible keep rotating to attract players to collect it
        transform.Rotate (new Vector3 (15, 30, 45) * Time.deltaTime);
    }

    void OnTriggerEnter(Collider c)
    {
        //after colliding with player, play sound, destroy self
        if(c.gameObject.tag == "Player")
        {
            this.collectibleAudio.Play();
            this.gameObject.SetActive(false);
        }
    }
}
