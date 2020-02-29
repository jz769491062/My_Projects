package itp341.zhu.zihan.finalprojectzhuzihan;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.Volley;
import com.github.twocoffeesoneteam.glidetovectoryou.GlideToVectorYou;
import com.github.twocoffeesoneteam.glidetovectoryou.GlideToVectorYouListener;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

import itp341.zhu.zihan.finalprojectzhuzihan.Model.Country;

public class SearchActivity extends AppCompatActivity {
    EditText SearchBar;
    ListView listCountry;
    Button SearchCountry,btncountrysearch,btntranslate,btntakequiz;
    private final String BASE_URL = "https://restcountries.eu/rest/v2/";
    private RequestQueue queue;//volley structure to manage multiple url requests
    private ArrayList<Country> Countries = new ArrayList<>();
    CountryAdapter Countryadapter = null;//custom adapter to hold country objects
    //The list of countries does not need to be shared across activities, so I did not use a singleton.
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);
        SearchBar = findViewById(R.id.Search_country_by_name);
        listCountry = findViewById(R.id.listView);
        SearchCountry = findViewById(R.id.button_search);
        btncountrysearch = findViewById(R.id.BtnCountrySearch);
        btntranslate = findViewById(R.id.BtnTranslate);
        btntakequiz = findViewById(R.id.BtnTakeQuiz);

        queue = Volley.newRequestQueue(this);//initializes volley queue

        //add 35 countries to the search page
        JsonArrayRequest req = new JsonArrayRequest(BASE_URL+"all",
                new Response.Listener<JSONArray>() {
                    @Override
                    public void onResponse(JSONArray response) {
                        try {
                            for (int i =0;i<35;i++){
                                //read the countries's name and flag
                                JSONObject countryData = response.getJSONObject(i*3);
                                Country temp = new Country();
                                temp.setName(countryData.getString("name"));
                                temp.setFlagUrl(countryData.getString("flag"));
                                Countries.add(temp);
                            }
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
        queue.add(req);//add the json request to the queue to make it download

        //load custom adapter
        Countryadapter = new CountryAdapter(this,R.layout.list_country,Countries);
        listCountry.setAdapter(Countryadapter);

        //direct to translate page
        btntranslate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),TranslateActivity.class);
                startActivity(i);

            }
        });
        //direct to quiz page
        btntakequiz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),QuizActivity.class);
                startActivity(i);
            }
        });
        //lead to details page
        SearchCountry.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getApplicationContext(),DetailActivity.class);
                i.putExtra(DetailActivity.COUNTRY_PASSED,SearchBar.getText().toString());
                startActivity(i);
            }
        });
        //when clicking on a country, lead to that country's details page
        listCountry.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                //TextView theCountryname = (TextView)findViewById(R.id.countrytext);
                String bla = Countries.get(position).getName();
                Intent i = new Intent(getApplicationContext(),DetailActivity.class);
                i.putExtra(DetailActivity.COUNTRY_PASSED,bla);
                startActivity(i);
            }
        });
    }

//custom adapter to hold the country information
    private class CountryAdapter extends ArrayAdapter<Country>{
        public CountryAdapter(Context context, int resource, List<Country> objects) {
            super(context, resource, objects);
        }
        @Override
        public View getView(int position, View convertView,ViewGroup parent) {
            if (convertView==null){
                //if does not exist , create/inflate row
                convertView = getLayoutInflater().inflate(R.layout.list_country,null);
            }
            TextView countryName = convertView.findViewById(R.id.countrytext);
            ImageView countryPic = convertView.findViewById(R.id.countrypic);

            //get current item to load into
            Country ct = getItem(position);
            //load country name and flag pictures
            countryName.setText(ct.getName());
            GlideToVectorYou.justLoadImage(SearchActivity.this, android.net.Uri.parse(ct.getFlagUrl()), countryPic);
            return convertView;
        }
    }
}
