using UnityEngine;

public class FailZone : MonoBehaviour
{
    void OnTriggerEnter(Collider collider)
    {
        Debug.Log(collider.gameObject.name);
        if (collider.gameObject.name == "Ball")
        {
            //GameObject.Find("GameManager").SendMessage("RestartGame");
            GameObject gm = GameObject.Find("GameManager");
            GameManager gmComponent = gm.GetComponent<GameManager>();
            //GameManager gmComponent = GameObject.Find("GameManager").GetComponent<GameManager>();
            gmComponent.RestartGame();
        }
    }

    void Start()
    {
    }

    void Update()
    {
    }
}