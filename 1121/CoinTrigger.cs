using UnityEngine;

public class CoinTrigger : MonoBehaviour
{
    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "Ball")
        {
            GameObject.Find("GameManager").SendMessage("GetCoin");
            Destroy(gameObject);
        }
    }

    void Start()
    {
    }

    void Update()
    {
    }
}