package itp341.zhu.zihan.finalprojectzhuzihan;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.Locale;

public class TranslateActivity extends AppCompatActivity {
    public static final String PREF = "pref stuff";
    public static final String PREF_IN = "pref i";
    public static final String PREF_OUT = "pref o";
    public static final String PREF_INTXT = "pref txt";
    Spinner InputSpin, OutputSpin;
    Button BtnToTrans, btncountrysearch, btntranslate, btntakequiz,btnswap;
    String BASE_URL = "https://translate.yandex.net/api/v1.5/tr.json/translate?";
    private RequestQueue queue;//volley structure to manage multiple url requests
    EditText IDInput, IDOutput;
    String[] languagetags,languagenames;
    SharedPreferences prefs;//sharedpreferences for storing the translate options
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_translate);
        InputSpin = findViewById(R.id.InputLanguageSpinner);
        OutputSpin = findViewById(R.id.OutputLanguageSpinner);
        BtnToTrans = findViewById(R.id.ButtonToTranslate);
        btncountrysearch = findViewById(R.id.BtnCountrySearch);
        btntranslate = findViewById(R.id.BtnTranslate);
        btntakequiz = findViewById(R.id.BtnTakeQuiz);
        IDInput = findViewById(R.id.ID_Input);
        IDOutput = findViewById(R.id.ID_Output);
        btnswap = findViewById(R.id.BtnSwap);


        //convert language tag to name
        languagetags = getResources().getStringArray(R.array.array_language);//a list of language tags
        languagenames = new String[18];//a list of language names
        for (int i=0; i<languagenames.length;i++){
            Locale loc = new Locale(languagetags[i]);
            languagenames[i] = loc.getDisplayLanguage(loc);
        }

        //populate Spinner according to language names
        ArrayAdapter<String> InputArray= new ArrayAdapter<String>(TranslateActivity.this,android.R.layout.simple_spinner_item,languagenames);
        InputArray.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        InputSpin.setAdapter(InputArray);
        final ArrayAdapter<String> OutputArray= new ArrayAdapter<String>(TranslateActivity.this,android.R.layout.simple_spinner_item,languagenames);
        OutputArray.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        OutputSpin.setAdapter(OutputArray);

        //use sharedpreferences to restore user's spinner selection and text entered
        prefs = getSharedPreferences(PREF,MODE_PRIVATE);
        if (prefs!=null){
            InputSpin.setSelection(prefs.getInt(PREF_IN,0),true);
            OutputSpin.setSelection(prefs.getInt(PREF_OUT,0),true);
            IDInput.setText(prefs.getString(PREF_INTXT,""));
        }

        //button for swapping the input and output language
        btnswap.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int inputlanIndex = InputSpin.getSelectedItemPosition();
                int outputlanIndex = OutputSpin.getSelectedItemPosition();
                InputSpin.setSelection(outputlanIndex,true);
                OutputSpin.setSelection(inputlanIndex,true);
            }
        });

        queue = Volley.newRequestQueue(this);//initializes volley queue

        BtnToTrans.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //get user's selected langauge
                int inputlanIndex = InputSpin.getSelectedItemPosition();
                int outputlanIndex = OutputSpin.getSelectedItemPosition();

                String totranslate = IDInput.getText().toString();
                String requeststr = BASE_URL +
                        "key=trnsl.1.1.20190501T053523Z.1614fb8845035f51.6da0eb1aed6514ad6eeac54384b95c20f681a356" +
                        "&text=" + totranslate + "&lang="+languagetags[inputlanIndex]+"-"+languagetags[outputlanIndex];
                //result returned as a JSON object
                JsonObjectRequest req = null;
                req = new JsonObjectRequest(Request.Method.GET,requeststr, null,
                        new Response.Listener<JSONObject>() {
                            @Override
                            public void onResponse(JSONObject response) {
                                System.out.println(response);
                                try {
                                    JSONArray wordtranslated = response.getJSONArray("text");
                                    IDOutput.setText(wordtranslated.getString(0));//display translated text
                                } catch (JSONException e) {
                                    e.printStackTrace();
                                }

                            }
                        },
                        new Response.ErrorListener() {
                            @Override
                            public void onErrorResponse(VolleyError error) {
                            }
                        });
                queue.add(req);//add the json request to the queue to make it download
                SaveTranslate();//call sharedpreferences to record user's language options and the text entered, easier to use when the user opens the app again
            }
        });

        //direct back to search page
        btncountrysearch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(), SearchActivity.class);
                startActivity(i);
            }
        });
        //direct to quiz page
        btntakequiz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(), QuizActivity.class);
                startActivity(i);
            }
        });

    }
    //save input and output language options and user's input text
    private void SaveTranslate() {
        prefs = getSharedPreferences(PREF,MODE_PRIVATE);
        SharedPreferences.Editor prefEditor = prefs.edit();
        prefEditor.putInt(PREF_IN,InputSpin.getSelectedItemPosition());
        prefEditor.putInt(PREF_OUT,OutputSpin.getSelectedItemPosition());
        prefEditor.putString(PREF_INTXT,IDInput.getText().toString());
        prefEditor.commit();
    }
}