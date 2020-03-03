//
//  SearchCityViewController.swift
//  TravelHelper
//
//  Created by 朱子涵 on 12/11/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import UIKit

class SearchCityViewController: UIViewController, UITextFieldDelegate {
    
    var instanceCityTable: CityTableViewController!
    @IBOutlet weak var SearchTF: UITextField!
    @IBOutlet weak var SeachButton: UIButton!
    @IBOutlet weak var NameLabel: UILabel!
    @IBOutlet weak var TemperatureLabel: UILabel!
    @IBOutlet weak var WeatherLabel: UILabel!
    @IBOutlet weak var AddToListButton: UIButton!
    private let cityModel = MyCityModel.sharedCityInstance
    var shouldHide : Bool = false
    var nameText : String = ""
    var tempText : String = ""
    var weatherText : String = ""
    override func viewDidLoad() {
        //notifies the user to type a city name and search
        super.viewDidLoad()
        SearchTF.delegate = self
        NameLabel.text = "Type city name and search"
        TemperatureLabel.text = ""
        WeatherLabel.text = ""
        TemperatureLabel.isHidden = true
        WeatherLabel.isHidden = true
        AddToListButton.isHidden = true
    }
    
    @IBAction func SearchStarted(_ sender: UIButton) {
        //Using OpenWeatherMap API
        //parse JSON
        guard let url = URL(string: "http://api.openweathermap.org/data/2.5/weather?q=\(SearchTF.text ?? "London")&appid=5f13ac917eebf0a61adefba522cff79d") else {return}
        let task = URLSession.shared.dataTask(with: url) { (data, response, error) in
            guard let dataResponse = data
                else {
                    print("Response Error\n")
                    return }
            do{
                let jsonResponse = try JSONSerialization.jsonObject(with:
                    dataResponse, options: [])
                //get data as json object
                guard let jsonObj = jsonResponse as? [String: Any] else {
                    print("jsonobj read fail \n")
                    return
                }
                if let code = jsonObj["cod"] as? Int{
                    //if 404 city not found, hide the "City:" "Weather:" texts and tell user to search again
                    if code == 404{
                        self.shouldHide = true
                    }
                    else{
                        self.shouldHide = false
                    }
                }
                //Then set our string variables
                if let weather = jsonObj["weather"] as? Array<Dictionary<String,Any>> {
                    if let main = weather[0]["main"] as? String{
                        //weatherText stores the weather description
                        self.weatherText = main
                    }
                }
                else{
                    print("result read fail \n")
                    self.shouldHide = true
                }
                if let temperature = jsonObj["main"] as? [String:Any]{
                    if var temp = temperature["temp"] as? Double{
                        temp -= 273.15
                        self.tempText = String(Int(temp)) + " Celsius"
                    }
                }
                if let name = jsonObj["name"] as? String{
                    self.nameText = name
                }
                DispatchQueue.main.async{
                    //use the string variables to set up text to display
                    if self.shouldHide {
                        //if city not found, notifies user to try again
                        self.NameLabel.text = "Cannot find city, try again"
                        self.TemperatureLabel.isHidden = true
                        self.WeatherLabel.isHidden = true
                        self.AddToListButton.isHidden = true
                    }
                    else{
                        self.TemperatureLabel.isHidden = false
                        self.WeatherLabel.isHidden = false
                        self.AddToListButton.isHidden = false
                        self.NameLabel.text = "City name: \(self.nameText)"
                        self.WeatherLabel.text = "Weather: \(self.weatherText)"
                        self.TemperatureLabel.text = "Temperature: \(self.tempText)"
                    }
                }
            } catch {
                print("Error")
            }
        }
        task.resume()
    }
    //back button
    @IBAction func CityBackClicked(_ sender: UIBarButtonItem) {
        dismiss(animated: true, completion: nil)
    }
    
    //Click add to list adds the city to the list and updates the city table
    @IBAction func AddToListClicked(_ sender: UIButton) {
        cityModel.addCity(name: nameText ,temperature: tempText,Weather: weatherText )
        instanceCityTable.tableView.reloadData()
        dismiss(animated: true, completion: nil)
    }
    //if user clicks somewhere else or return, dismisses keyboard
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
           super.touchesBegan(touches, with: event)
           let touch = touches.first
           if SearchTF.isFirstResponder && touch?.view != SearchTF {
               SearchTF.resignFirstResponder()
           }
       }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        self.view.endEditing(true)
        return false
    }
}
