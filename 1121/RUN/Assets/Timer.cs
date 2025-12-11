using UnityEngine;
using TMPro;

public class Timer : MonoBehaviour
{
    public static float time;
    
    void Start()
    {
        time = 0;
    }
    
    void Update()
    {
        if(GoalArea.goal == false)
        {
            time += Time.deltaTime;
        }
        
        int t = Mathf.FloorToInt(time);
        TextMeshProUGUI uiText = GetComponent<TextMeshProUGUI>();
        uiText.text = "Time : " + t.ToString();
    }
}