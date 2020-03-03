//
//  CountryDetailViewController.swift
//  TravelHelper
//
//  Created by Zihan Zhu on 12/9/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import UIKit
import WebKit

class CountryDetailViewController: UIViewController {

    @IBOutlet weak var CountryNameLabel: UILabel!

    @IBOutlet weak var FlagWebView: WKWebView!
    
    @IBOutlet weak var CapitalLabel: UILabel!
    @IBOutlet weak var CurrencyLabel: UILabel!
    @IBOutlet weak var AreaLabel: UILabel!
    @IBOutlet weak var TimezoneLabel: UILabel!
    @IBOutlet weak var PopLabel: UILabel!
    @IBOutlet weak var LangLabel: UILabel!
    
    @IBOutlet weak var GoogleMapButton: UIButton!
    
    private let countryModel = CountriesModel.sharedInstance
    public var countryPassed: Country? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //populate fields with the Country object data passed in
        if( countryPassed != nil){
        CountryNameLabel.text = countryPassed?.getName()
        CapitalLabel.text = "Capital: " + (countryPassed?.getCapital() ?? "")
        //load flag image using WKWebView
        let flagurlstr = countryPassed?.getFlagUrl() ?? ""
        let url = URL(string: flagurlstr )
        FlagWebView.frame = self.view.bounds
        FlagWebView.contentMode = .scaleToFill
        FlagWebView.load(URLRequest(url: url!))
        CurrencyLabel.text = "Currency: " + (countryPassed?.getCurrency() ?? "")
        AreaLabel.text = "Area: " + (countryPassed?.getArea() ?? "") + " sq. km2"
        TimezoneLabel.text = "Timezone: " + (countryPassed?.getTimezone() ?? "")
        PopLabel.text = "Population: " + (countryPassed?.getPopulation() ?? "")
        LangLabel.text = "Language: " + (countryPassed?.getLanguage() ?? "")
        }
        else{
            //The country name must be the official one, like "United States of America"
            CountryNameLabel.text = "Country name does not exist, please go back"
            CapitalLabel.text = ""
            CurrencyLabel.text = ""
            AreaLabel.text = ""
            TimezoneLabel.text = ""
            PopLabel.text = ""
            LangLabel.text = ""
            GoogleMapButton.isHidden = true
        }
    }
    
    @IBAction func GoogleMapClicked(_ sender: UIButton) {
        //set the target country for the Google Map
        countryModel.targetCountry = CountryNameLabel.text ?? "United States"
    }
    
    @IBAction func BackButtonClicked(_ sender: UIButton) {
        dismiss(animated: true, completion: nil)
    }
    
    // MARK: - Navigation
    /*
    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        
    }*/
}
