//
//  MyCityModel.swift
//  TravelHelper
//
//  Created by 朱子涵 on 12/11/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import Foundation

class MyCityModel:NSObject{
    //The model used for loading the list of cities in the weather tab.
    //read a local plist and populate data
    private var myCities : [City]
    //Singleton used when in the city table view and the search city view
    public static let sharedCityInstance = MyCityModel()
    var filePath : String
    override init() {
        myCities = []
        let manager = FileManager.default
        filePath = ""
        super.init()
        if let url = manager.urls(for: .documentDirectory,
                                  in: .userDomainMask).first {
            //load local plist, print path for reference
            filePath = url.appendingPathComponent("mycity.plist").path
            print("For your convenience: " + filePath + "\n")
        }
        if manager.fileExists(atPath: filePath) {
            if let cityArray = NSArray(contentsOfFile: filePath) {
                for dict in cityArray {
                    //nameK is name of the city
                    //mainK is the weather description
                    //temperatureK is the temperature in Celsius
                    let cityDict = dict as! [String: String]
                    if let nameString = cityDict["nameK"],
                        let mainString = cityDict["mainK"], let temperatureString = cityDict["temperatureK"] {
                        let city = City(name: nameString, main: mainString, temperature: temperatureString)
                        myCities.append(city)
                    }
                }
            }
            if numberOfCities() == 0 {
                //if there are no cities in plist, add our 2 default cities
                let city1 = City(name: "Miami", main: "Sunny", temperature: "30 Celsius")
                myCities.append(city1)
                let city2 = City(name: "Tokyo", main: "Clouds", temperature: "15 Celsius")
                myCities.append(city2)
            }
        } else {
            //add 2 cities
            let city1 = City(name: "Miami", main: "Sunny", temperature: "30 Celsius")
            myCities.append(city1)
            let city2 = City(name: "Tokyo", main: "Clouds", temperature: "15 Celsius")
            myCities.append(city2)
        }
    }
    
    func save() {
        //save the city list to our plist
        var cityArray = [[String:String]]()
        for c in myCities {
            let dict = ["nameK": c.getName(),
                        "mainK": c.getMain(),
                        "temperatureK": c.getTemperature()]
            cityArray.append(dict)
        }
        (cityArray as NSArray).write(toFile: filePath, atomically: true)
    }
    
    func numberOfCities() -> Int {
        return myCities.count
    }
    //returns city at the designated index
    func city(at index: Int) -> City? {
        if numberOfCities() == 0 {
            return nil
        }
        if index >= 0 && index < myCities.count{
            return myCities[index]
        }
        return nil
    }
    //remove a city
    func removeCity(at index: Int) {
        if numberOfCities() == 0 {
            return
        }
        if index >= 0 && index < myCities.count {
            myCities.remove(at: index)
        }
        save()
    }
    //add (actually append) a city to the list
    func addCity(name:String, temperature:String,Weather:String){
        let ct = City(name: name, main: Weather, temperature: temperature)
        myCities.append(ct)
        save()
    }
    //do save() again in the end
    deinit{
        save()
    }
    
}
