//
//  CountryTableViewController.swift
//  TravelHelper
//
//  Created by Zihan Zhu on 12/9/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import UIKit

class CountryTableViewController: UITableViewController,UITextFieldDelegate {
    
    private let countryModel = CountriesModel.sharedInstance
    @IBOutlet weak var SearchCountryTF: UITextField!
    @IBOutlet weak var CountrySearchButton: UIButton!
    override func viewDidLoad() {
        super.viewDidLoad()
        SearchCountryTF.text = ""
        SearchCountryTF.delegate = self
        //Data might not show up if json parsing haven't finished yet in CountriesModel
        //So we do reload again to ensure the table will be populated
        self.tableView?.reloadData()
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return countryModel.numberOfCountries()
    }

    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "CountryCell", for: indexPath)
        //Populate cells with country names
        if let label = cell.textLabel {
            let country = countryModel.country(at: indexPath.row)
                label.text = country?.getName()
        }
        return cell
    }
    
    //dismisses keyboard if user clicks somewhere else
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        super.touchesBegan(touches, with: event)
        let touch = touches.first
        if SearchCountryTF.isFirstResponder && touch?.view != SearchCountryTF {
            SearchCountryTF.resignFirstResponder()
        }
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        self.view.endEditing(true)
        return false
    }
    
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
        if segue.identifier == "DetailCellSegue" {//if user clicks on a cell
                if let DetailVC = segue.destination as? CountryDetailViewController {
                    guard let cellrow = tableView.indexPath( for: sender as! UITableViewCell)?.row else { return }
                    if let countryToShow = countryModel.country(at:cellrow ){
                        DetailVC.countryPassed = countryToShow
                    }
                    else {return}
                }
        }
        else if segue.identifier == "DetailTextSegue" {// if user clicks search button
            if let DetailVC = segue.destination as? CountryDetailViewController {
                //find country by name to get the corresponding Country object
                if let countryToShow = countryModel.searchCountryByName(countryName: SearchCountryTF?.text ?? "Germany"){
                    DetailVC.countryPassed = countryToShow
                }
                else {return}
            }
        }
    }
}
