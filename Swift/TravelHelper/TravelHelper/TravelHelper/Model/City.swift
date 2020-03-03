//
//  City.swift
//  TravelHelper
//
//  Created by Zihan Zhu on 12/9/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import Foundation

struct City{
    //The model for the weather info of a city
    //all in String format
    private var Name : String
    private var Main : String
    private var Temperature : String
    
    init(name:String,main:String,temperature:String){
        self.Name = name
        self.Main = main
        self.Temperature = temperature
    }
    //getters
    public func getName()->String{
        return Name
    }
    
    public func getMain()->String{
        return Main
    }
    
    public func getTemperature()->String{
        return Temperature
    }
    
    
}
