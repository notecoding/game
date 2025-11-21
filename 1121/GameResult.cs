using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameResult : MonoBehaviour
{
    private int highScore;
    public Text resultTime;
    public Text bestTime;
    public GameObject parts;

    void Start()
    {
        if (PlayerPrefs.HasKey("HighScore"))
        {
            highScore = PlayerPrefs.GetInt("HighScore");
        }
        else
        {
            highScore = 999;
        }
    }

    void Update()
    {
        if (GoalArea.goal)
        {
            parts.SetActive(true);
            int result = Mathf.FloorToInt(Timer.time);
            resultTime.text = "ResultTime " + result;
            bestTime.text = "BestTime " + highScore;

            if (highScore > result)
            {
                PlayerPrefs.SetInt("HighScore", result);
            }
        }
    }

    public void OnRetry()
    {
        SceneManager.LoadScene("Main");
    }
}
