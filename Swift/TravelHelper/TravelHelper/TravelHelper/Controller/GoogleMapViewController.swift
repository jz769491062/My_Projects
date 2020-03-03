//
//  GoogleMapViewController.swift
//  TravelHelper
//
//  Created by Zihan Zhu on 12/9/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import UIKit
import GoogleMaps

class GoogleMapViewController: UIViewController {
    
    private var latitude: Double?
    private var longitude: Double?
    private let countryModel = CountriesModel.sharedInstance
    
    @IBOutlet weak var MapView: UIView!//where the map will load
    var mapView: GMSMapView!//the map view used for setup
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //Set up a default map that points to Sydney
        let camera = GMSCameraPosition.camera(withLatitude: -33, longitude: 151, zoom: 5.0)
        self.mapView = GMSMapView.map(withFrame: MapView.bounds, camera: camera)
        self.MapView.addSubview(mapView!)
        //Then call the Google Map API, change camera and set marker
        callAPI()
    }
    
    func callAPI() {
        //parse response from Google Map API
        //get the target country to search from the singleton
        if let countryName = countryModel.targetCountry{
            guard let url = URL(string: "https://maps.googleapis.com/maps/api/geocode/json?address=\(countryName)&key=AIzaSyCO7i-00D6R1fAZuJLeM232Ckwwflo_KH0")
            else {return}
            let task = URLSession.shared.dataTask(with: url) { (data, response, error) in
                guard let dataResponse = data
                    else {
                        print("Response Error\n")
                        return }
                do{
                    let jsonResponse = try JSONSerialization.jsonObject(with:
                        dataResponse, options: [])
                    //get json response as a json object
                    guard let jsonObj = jsonResponse as? [String: Any] else {
                        print("jsonobj read fail \n")
                        return
                    }
                    guard let results = jsonObj["results"] as? Array<Dictionary<String,Any>>
                    else {
                        print("result read fail \n")
                        return
                    }
                    if let geometry = results[0]["geometry"] as? [String: Any]{
                        if let location = geometry["location"] as? [String: Double]{
                            self.latitude = location["lat"] ?? -33.86
                            self.longitude = location["lng"] ?? 151.20
                            let templat : CLLocationDegrees = CLLocationDegrees(floatLiteral: self.latitude ?? -33.86)
                            let templng : CLLocationDegrees = CLLocationDegrees(floatLiteral: self.longitude ?? 151.20)
                            // update camera variable
                            let camera = GMSCameraPosition.camera(withLatitude: templat, longitude: templng, zoom: 5.0)
                            //in main thread, update camera and marker
                            DispatchQueue.main.async{
                                self.mapView.animate(to: camera)
                                let marker = GMSMarker()
                                marker.position = CLLocationCoordinate2D(latitude: templat, longitude: templng)
                                marker.map = self.mapView
                            }
                        }
                        else{
                            print("location read fail \n")
                        }
                    }
                    else{
                        print("geometry read fail \n")
                    }
                } catch {
                    print("Error reading Google Map JSON\n")
                }
            }
            task.resume()
        }
        else {return}
    }
    
    @IBAction func BackClicked(_ sender: UIBarButtonItem) {
        //back button
        dismiss(animated: true, completion: nil)
    }
}

/*
 // MARK: - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
 // Get the new view controller using segue.destination.
 // Pass the selected object to the new view controller.
 }
 */
