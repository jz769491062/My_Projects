//
//  CityTableViewController.swift
//  TravelHelper
//
//  Created by 朱子涵 on 12/11/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import UIKit

class CityTableViewController: UITableViewController {

    private let cityModel = MyCityModel.sharedCityInstance
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
         self.navigationItem.leftBarButtonItem = self.editButtonItem
    }

    // MARK: - Table view data source

    override func viewWillAppear(_ animated: Bool) {
        //refresh table when this view will appear
        tableView?.reloadData()
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        //return the number of rows
        return cityModel.numberOfCities()
    }

    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "CityCell", for: indexPath)

        // Configure the cell...
        if let label = cell.textLabel {
            if let sublabel = cell.detailTextLabel{
                let city = cityModel.city(at: indexPath.row)
                //main label is city name, sublabel is weather description and temperature
                label.text = city?.getName()
                sublabel.text = "\(city?.getMain() ?? ""), \(city?.getTemperature() ?? "")"
            }
        }
        return cell
    }

    // Override to support editing the table view.
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            // Delete the row from the data source
            cityModel.removeCity(at: indexPath.row)
            // Then remove in our view
            tableView.deleteRows(at: [indexPath], with: .fade)
        }
    }
    
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
        if segue.identifier == "SearchCitySegue"{
            if let SearchVC = segue.destination as? SearchCityViewController {
                //pass an instance of city table to refresh table in time
                SearchVC.instanceCityTable = self
            }
        }
    }
}
