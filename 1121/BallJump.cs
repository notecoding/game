using UnityEngine;

public class BallJump : MonoBehaviour
{
    void Start()
    {
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            GetComponent<Rigidbody>().AddForce(Vector3.up * 300);
        }
    }
}