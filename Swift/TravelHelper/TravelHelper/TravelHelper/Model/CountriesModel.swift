//
//  CountriesModel.swift
//  TravelHelper
//
//  Created by Zihan Zhu on 12/9/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import Foundation

class CountriesModel:NSObject{
    //The singleton model that holds the countries' info got from REST Countries API.
    private var countries: [Country]
    // Swift Singleton pattern
    public static let sharedInstance = CountriesModel()
    var baseURL : String
    public var targetCountry: String?
    
    override init() {
        //Using the REST Countries API
        countries = []
        baseURL = "https://restcountries.eu/rest/v2/"
        super.init()
        //start parsing the REST Countries JSON
        guard let url = URL(string: baseURL + "all") else {return}
        let task = URLSession.shared.dataTask(with: url) { (data, response, error) in
            guard let dataResponse = data
                else {
                    print("Response Error\n")
                    return }
            do{
                let jsonResponse = try JSONSerialization.jsonObject(with:
                    dataResponse, options: [])
                //get JSON array data
                guard let jsonArray = jsonResponse as? [[String: Any]] else {
                    return
                }
                var i = 0
                while i < 250 {//load 250 countries
                    //if any field fails to load (which will not happen in most cases),
                    //just continue on loading the next country's data
                    guard let name = jsonArray[i]["name"] as? String else {
                        i += 1; continue;
                    }
                    guard let flagurl = jsonArray[i]["flag"] as? String else {
                        i += 1; continue;
                    }
                    guard let pop = jsonArray[i]["population"] as? Int else {
                        i += 1; continue;
                    }
                    guard let languages = jsonArray[i]["languages"] as? Array<Dictionary<String,String>> else {
                        i+=1; continue;
                    }
                    //just display 1 timezone
                    guard let timezones = jsonArray[i]["timezones"] as? Array<String> else {
                        i += 1; continue;
                    }
                    guard let area = jsonArray[i]["area"] as? Double else {
                        i += 1; continue;
                    }
                    guard let currencies = jsonArray[i]["currencies"] as? Array<Dictionary<String,String>> else {
                        i += 1; continue;
                    }
                    guard let capital = jsonArray[i]["capital"] as? String else {
                        i += 1; continue;
                    }
                    //create new Country object and insert to the list of countries
                    let newcountry = Country(name: name, flagurl: flagurl, population: String(pop), language: languages[0]["name"] ?? "", timezone: timezones[0], area: String(area), currency: currencies[0]["name"] ?? "", capital: capital)
                    self.countries.append(newcountry)
                    i += 1
                }
            } catch {
                print("Error")
            }
        }
        task.resume()
    }
    func numberOfCountries() -> Int {
        return countries.count
    }
    //return Country object at a designated index
    func country(at index: Int) -> Country? {
        if numberOfCountries() == 0 {
            return nil
        }
        if index >= 0 && index < countries.count{
            return countries[index]
        }
        return nil
    }
    func searchCountryByName(countryName: String)->Country?{
        for ctr in countries {
            if countryName.lowercased() == ctr.getName().lowercased(){
                return ctr
            }
        }
        return nil
    }
    
}
