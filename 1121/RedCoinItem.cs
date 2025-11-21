using UnityEngine;

public class RedCoinItem : MonoBehaviour
{
    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "Ball")
        {
            GameObject.Find("GameManager").SendMessage("RedCoinStart");
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