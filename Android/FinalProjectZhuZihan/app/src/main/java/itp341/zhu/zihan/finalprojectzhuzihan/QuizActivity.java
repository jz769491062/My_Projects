package itp341.zhu.zihan.finalprojectzhuzihan;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.RequestQueue;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

public class QuizActivity  extends AppCompatActivity {
    Button choice1,choice2,choice3,choice4,btncountrysearch,btntranslate,btntakequiz;
    TextView TextQuestion;
    ArrayList<String> correct_answers = new ArrayList<>();
    ArrayList<String> Questions =new ArrayList<>();

    ArrayList<String> incorrect_answers=new ArrayList<>();

    int CurrentIndex =0;
    int score =0;
    private RequestQueue queue;//volley structure to manage multiple url requests
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_quiz);
        btncountrysearch = findViewById(R.id.BtnCountrySearch);
        btntranslate = findViewById(R.id.BtnTranslate);
        btntakequiz = findViewById(R.id.BtnTakeQuiz);
        TextQuestion = findViewById(R.id.QuestionText);
        choice1 = findViewById(R.id.Choice1);
        choice2 = findViewById(R.id.Choice2);
        choice3 = findViewById(R.id.Choice3);
        choice4 = findViewById(R.id.Choice4);

            String json = null;
            //read quizzes from local json file
            try {
                InputStream istr = getApplicationContext().getAssets().open("quiz.json");
                byte[] buffer = new byte[istr.available()];
                istr.read(buffer);
                json = new String(buffer, "UTF-8");//support universal language
                istr.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        //load json content
        queue = Volley.newRequestQueue(this);//initializes volley queue
        try {
            JSONArray AllQuiz = new JSONObject(json).getJSONArray("results");
            for (int i=0;i<AllQuiz.length();i++){
                Questions.add(AllQuiz.getJSONObject(i).getString("question"));
                correct_answers.add(AllQuiz.getJSONObject(i).getString("correct_answer"));
                for (int j=0;j<3;j++){
                    incorrect_answers.add(AllQuiz.getJSONObject(i).getJSONArray("incorrect_answers").getString(j));
                }
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }

        UpdateQuestion();
        //show true or false based on which button user clicked
        //if user is at the last question,the quiz score is also displayed after user finishes the last quiz question
        choice1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                CurrentIndex = (CurrentIndex+1)%Questions.size();
                Toast.makeText(getApplicationContext(),"False",Toast.LENGTH_SHORT).show();
                if (CurrentIndex==0){
                    Toast.makeText(getApplicationContext(),"Your Score: "+score+"/"+Questions.size(),Toast.LENGTH_LONG).show();
                    score =0;
                }
                UpdateQuestion();
            }
        });
        choice2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                CurrentIndex = (CurrentIndex+1)%Questions.size();
                Toast.makeText(getApplicationContext(),"False",Toast.LENGTH_SHORT).show();
                if (CurrentIndex==0){
                    Toast.makeText(getApplicationContext(),"Your Score: "+score+"/"+Questions.size(),Toast.LENGTH_LONG).show();
                    score =0;
                }
                UpdateQuestion();
            }
        });
        choice4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                CurrentIndex = (CurrentIndex+1)%Questions.size();
                Toast.makeText(getApplicationContext(),"False",Toast.LENGTH_SHORT).show();
                if (CurrentIndex==0){
                    Toast.makeText(getApplicationContext(),"Quiz Finished! Your Score: "+score+"/"+Questions.size(),Toast.LENGTH_LONG).show();
                    score =0;
                }
                UpdateQuestion();
            }
        });
        choice3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                CurrentIndex = (CurrentIndex+1)%Questions.size();
                Toast.makeText(getApplicationContext(),"Correct",Toast.LENGTH_SHORT).show();
                score++;
                if (CurrentIndex==0){
                    Toast.makeText(getApplicationContext(),"Your Score: "+score+"/"+Questions.size(),Toast.LENGTH_LONG).show();
                    score =0;
                }
                UpdateQuestion();//update the question and answer content so the next question is displayed
            }
        });

        //direct back to search page
        btncountrysearch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),SearchActivity.class);
                startActivity(i);
            }
        });
        //direct to translate page
        btntranslate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),TranslateActivity.class);
                startActivity(i);
            }
        });
    }

    public void UpdateQuestion(){
        TextQuestion.setText(CurrentIndex+1+". "+Questions.get(CurrentIndex));
        choice1.setText(incorrect_answers.get(CurrentIndex*3));
        choice2.setText(incorrect_answers.get(CurrentIndex*3+1));
        choice3.setText(correct_answers.get(CurrentIndex));
        choice4.setText(incorrect_answers.get(CurrentIndex*3+2));
    }

}
