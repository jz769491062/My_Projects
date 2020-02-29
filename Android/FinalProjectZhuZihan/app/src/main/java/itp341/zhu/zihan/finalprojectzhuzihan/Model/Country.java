package itp341.zhu.zihan.finalprojectzhuzihan.Model;

public class Country {
    public String Name,FlagUrl,Population,Language,TimeZone,Area,Currency,Capital;

    public Country(){
        Name ="";
        FlagUrl = "";
        Population = "";
        Language = "";
        TimeZone = "";
        Area ="";
        Currency = "";
        Capital = "";
    }

    public Country(String name, String flagUrl, String Population,String Language, String timeZone, String area, String currency, String capital) {
        Name = name;
        FlagUrl = flagUrl;
        this.Population = Population;
        this.Language = Language;
        TimeZone = timeZone;
        Area = area;
        Currency = currency;
        Capital = capital;
    }

    @Override
    public String toString() {
        return "CountryCardView{" +
                "Name='" + Name + '\'' +
                ", FlagUrl='" + FlagUrl + '\'' +
                ", Population='" + Population + '\'' +
                ", Language='" + Language + '\'' +
                ", TimeZone='" + TimeZone + '\'' +
                ", Area='" + Area + '\'' +
                ", Currency='" + Currency + '\'' +
                ", Capital='" + Capital + '\'' +
                '}';
    }

    public String getName() {
        return Name;
    }

    public String getFlagUrl() {
        return FlagUrl;
    }

    public String getPopulation() {
        return Population;
    }

    public String getLanguage() {
        return Language;
    }

    public String getTimeZone() {
        return TimeZone;
    }

    public String getArea() {
        return Area;
    }

    public String getCurrency() {
        return Currency;
    }

    public String getCapital() {
        return Capital;
    }

    public void setName(String name) {
        Name = name;
    }

    public void setFlagUrl(String flagUrl) {
        FlagUrl = flagUrl;
    }

    public void setPopulation(String population) {
        Population = population;
    }

    public void setLanguage(String language) {
        Language = language;
    }

    public void setTimeZone(String timeZone) {
        TimeZone = timeZone;
    }

    public void setArea(String area) {
        Area = area;
    }

    public void setCurrency(String currency) {
        Currency = currency;
    }

    public void setCapital(String capital) {
        Capital = capital;
    }
}
