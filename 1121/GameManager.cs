using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class GameManager : MonoBehaviour
{
    public int coinCount = 0;
    public TextMeshProUGUI coinText;
    
    void GetCoin()
    {
        coinCount++;
        coinText.text = coinCount + "";
        Debug.Log("동전 : " + coinCount);
    }
    
    public void RestartGame()
    {
        SceneManager.LoadScene(0);
    }
    
    void RedCoinStart()
    {
        DestroyObstacles();
    }
    
    void DestroyObstacles()
    {
        GameObject[] obstacles = GameObject.FindGameObjectsWithTag("Obstacle");
        for (int i = 0; i < obstacles.Length; i++)
        {
            Destroy(obstacles[i]);
        }
    }

    void Start()
    {
    }

    void Update()
    {
    }
}