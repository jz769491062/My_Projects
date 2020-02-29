package itp341.zhu.zihan.finalprojectzhuzihan;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.Volley;
import com.github.twocoffeesoneteam.glidetovectoryou.GlideToVectorYou;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import itp341.zhu.zihan.finalprojectzhuzihan.Model.Country;


public class DetailActivity extends AppCompatActivity {
    public static final String COUNTRY_PASSED = "";
    public int Lat,Lng;
    TextView CountryName;
    TextView TextLanguage,TextPopulation,TextTimezone,TextArea,TextCurrency,TextCapital;
    Button Search,Translate,Quiz,Googlemap;
    ImageView Flagpic;
    private RequestQueue queue;
    private final String BASE_URL = "https://restcountries.eu/rest/v2/name/";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);
        CountryName = findViewById(R.id.CountryNameText);
        Flagpic = findViewById(R.id.FlagPic);
        Googlemap = findViewById(R.id.GoogleMap);
        Search = findViewById(R.id.BtnCountrySearch);
        Translate = findViewById(R.id.BtnTranslate);
        Quiz = findViewById(R.id.BtnTakeQuiz);
        TextLanguage = findViewById(R.id.TextLanguage);
        TextPopulation = findViewById(R.id.TextPopulation);
        TextTimezone = findViewById(R.id.TextTimezone);
        TextArea = findViewById(R.id.TextArea);
        TextCurrency = findViewById(R.id.TextCurrency);
        TextCapital = findViewById(R.id.TextCapital);

        Intent i = getIntent();
        String thecountry = i.getStringExtra(COUNTRY_PASSED);


        queue = Volley.newRequestQueue(this);//initializes volley queue

        //add 30 countries to the search page
        JsonArrayRequest req = new JsonArrayRequest(BASE_URL+thecountry,
                new Response.Listener<JSONArray>() {
                    @Override
                    public void onResponse(JSONArray response) {
                        try {
                            JSONObject countryData = response.getJSONObject(0);
                            CountryName.setText(countryData.getString("name"));
                            JSONArray countryLan = countryData.getJSONArray("languages");
                            StringBuilder strBuilder = new StringBuilder("Language: ");
                            for (int i =0; i<countryLan.length();i++){
                                JSONObject obj = countryLan.getJSONObject(i);
                                String lang = obj.getString("name");
                                strBuilder.append(lang);
                                strBuilder.append(" ");
                            }
                            String str = strBuilder.toString();
                            TextLanguage.setText(str);
                            TextPopulation.setText("Population: " +String.valueOf(countryData.getInt("population")));
                            //for practical purposes, display the first major timezone for a country only
                            TextTimezone.setText("Timezone: " + countryData.getJSONArray("timezones").getString(0));
                            TextArea.setText("Area: " +String.valueOf(countryData.getInt("area") +  "km^2"));
                            //populating information related to that country
                            JSONArray countryCur = countryData.getJSONArray("currencies");
                            StringBuilder strBuild = new StringBuilder("Currency: ");
                            for (int i =0; i<countryCur.length();i++){
                                JSONObject obj = countryCur.getJSONObject(i);
                                String cur = obj.getString("name");
                                strBuild.append(cur);
                                strBuild.append(" ");
                            }
                            String strcur = strBuild.toString();
                            TextCurrency.setText(strcur);
                            TextCapital.setText("Capital: " +countryData.getString("capital"));
                            //prepare latitude and logitude for GoogleMap to display
                            Lat = countryData.getJSONArray("latlng").getInt(0);
                            Lng = countryData.getJSONArray("latlng").getInt(1);
                            GlideToVectorYou.justLoadImage(DetailActivity.this, android.net.Uri.parse(countryData.getString("flag")), Flagpic);//load country flag pictures
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }

                    }
                },
                new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        //gets called when error

                    }
                }
        );
        queue.add(req);

        //Go to Google Map page
        Googlemap.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),MapsActivity.class);
                i.putExtra(MapsActivity.LAT,Lat);
                i.putExtra(MapsActivity.LNG,Lng);
                System.out.println(Lat);
                System.out.println(Lng);
                startActivity(i);
            }
        });

        //direct back to search page
        Search.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),SearchActivity.class);
                startActivity(i);
            }
        });
        //direct to translate page
        Translate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),TranslateActivity.class);
                startActivity(i);
            }
        });
        //direct to quiz page
        Quiz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),QuizActivity.class);
                startActivity(i);
            }
        });
    }

}
