//
//  TranslateDetailViewController.swift
//  TravelHelper
//
//  Created by 朱子涵 on 12/11/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import UIKit

class TranslateDetailViewController: UIViewController {

    @IBOutlet weak var DetailLabel: UILabel!
    public var textToShow:String = ""
    override func viewDidLoad() {
        super.viewDidLoad()
        //acquire the texts passed in and display it with a larger size
        DetailLabel.text = textToShow
    }
    //back button
    @IBAction func BackButtonClicked(_ sender: UIBarButtonItem) {
        dismiss(animated: true, completion: nil)
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
