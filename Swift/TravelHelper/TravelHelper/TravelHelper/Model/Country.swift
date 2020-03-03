//
//  Country.swift
//  TravelHelper
//
//  Created by Zihan Zhu on 12/9/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import Foundation

struct Country {
    //The model for the info of a country
    private var Name : String
    private var FlagUrl : String//the url of national flag
    private var Population : String
    private var Language : String
    private var TimeZone : String
    private var Area : String
    private var Currency : String
    private var Capital : String
    init(name:String,flagurl:String,population:String,language:String,timezone:String,area:String,currency:String,capital:String){
        self.Name = name
        self.FlagUrl = flagurl
        self.Population = population
        self.Language = language
        self.TimeZone = timezone
        self.Area = area
        self.Currency = currency
        self.Capital = capital
    }
    //getters
    public func getName()->String{
        return Name
    }
    
    public func getFlagUrl()->String{
        return FlagUrl
    }
    
    public func getPopulation()->String{
        return Population
    }
    
    public func getLanguage()->String{
        return Language
    }
    
    public func getTimezone()->String{
        return TimeZone
    }
    
    public func getArea()->String{
        return Area
    }
    
    public func getCurrency()->String{
        return Currency
    }
    
    public func getCapital()->String{
        return Capital
    }
}
