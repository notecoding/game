using UnityEngine;

public class Shooter : ObstacleMove
{
    public GameObject stone;
    
    float timeCount = 0;

    new void Update()
    {
        base.Update();
        timeCount += Time.deltaTime;
        if (timeCount > 3)
        {
            //Debug.Log("돌을 던져라");
            Instantiate(stone, transform.position, Quaternion.identity);
            timeCount = 0;
        }
    }
}