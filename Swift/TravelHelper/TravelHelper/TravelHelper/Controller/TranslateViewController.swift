//
//  TranslateViewController.swift
//  TravelHelper
//
//  Created by 朱子涵 on 12/11/19.
//  Copyright © 2019 Zihan Zhu. All rights reserved.
//

import UIKit

//https://github.com/hackiftekhar/IQKeyboardManager/issues/1616
//The unable to simultaneously satisfy constraints error is likely a bug in the latest XCode 11 release.
//The UIViewAlertForUnsatisfiableConstraints should not affect the app's performance.
//Alert shows up in 8 Plus but not in other simulators. switching between textfields has a small change of triggering it.

class TranslateViewController: UIViewController,UIPickerViewDelegate, UIPickerViewDataSource, UITextFieldDelegate {
    
    @IBOutlet weak var InputTF: UITextField!
    @IBOutlet weak var outputTF: UITextField!
    @IBOutlet weak var TranslateButton: UIButton!
    @IBOutlet weak var LanguagePicker: UIPickerView!
    @IBOutlet weak var InputLangButton: UIButton!
    @IBOutlet weak var OutputLangButton: UIButton!
    
    var translated :String = "translated string goes here"
    var mapLangCode : Dictionary<String,String> = [:] //maps language name to the corresponding language code
    var SelectingInput : Bool = false//used for modifying the corresponding button title
    var SelectingOutput : Bool = false
    override func viewDidLoad() {
        InputTF.delegate = self
        outputTF.delegate = self
        LanguagePicker.isHidden = true
        //adjust button label text so it fits in one line
        InputLangButton.titleLabel?.adjustsFontSizeToFitWidth = true;
        OutputLangButton.titleLabel?.adjustsFontSizeToFitWidth = true;
        //get languages supported by English UI
        guard let url = URL(string: "https://translate.yandex.net/api/v1.5/tr.json/getLangs?ui=en&key=trnsl.1.1.20191211T085306Z.917204ec77f34875.800663e5095eb549fb88eac2c16a14b78c9a7361") else {return}
        let task = URLSession.shared.dataTask(with: url) { (data, response, error) in
            guard let dataResponse = data
                else {
                    print("Response Error\n")
                    return }
            do{
                let jsonResponse = try JSONSerialization.jsonObject(with:
                    dataResponse, options: [])
                //get json object data
                guard let jsonObj = jsonResponse as? [String: Any] else {
                    print("jsonobj read fail \n")
                    return
                }
                guard let langs = jsonObj["langs"] as? [String:String] else {
                    print("langs read fail \n")
                    return
                }
                for (key,value) in langs{
                    //revert order so English matches to en instead of the opposite way
                    self.mapLangCode[value] = key
                }
                DispatchQueue.main.async{
                    //Use the UIPickerViewDelegate and UIPickerViewDataSource to populate picker with our dictionary
                    self.LanguagePicker.delegate = self
                    self.LanguagePicker.dataSource = self
                }
            } catch {
                print("Error")
            }
        }
        task.resume()
    }
    
    //when the translate button is clicked, start translation
    @IBAction func TranslateClicked(_ sender: UIButton) {
        //Using the Yandex Translate API
        //if user did not select an input/output language, defaults to English(en)
        guard let url = URL(string: "https://translate.yandex.net/api/v1.5/tr.json/translate?key=trnsl.1.1.20191211T085306Z.917204ec77f34875.800663e5095eb549fb88eac2c16a14b78c9a7361&text=\(InputTF.text ?? "")&lang=\(mapLangCode[InputLangButton.titleLabel?.text ?? "en"] ?? "en")-\(mapLangCode[OutputLangButton.titleLabel?.text ?? "en"] ?? "en")") else {return}
        let task = URLSession.shared.dataTask(with: url) { (data, response, error) in
            guard let dataResponse = data
                else {
                    print("Response Error\n")
                    return }
            do{
                let jsonResponse = try JSONSerialization.jsonObject(with:
                    dataResponse, options: [])
                //get data
                guard let jsonObj = jsonResponse as? [String: Any] else {
                    print("jsonobj read fail \n")
                    return
                }
                if let code = jsonObj["code"] as? Int{
                    if code != 200{
                        //if code is not 200(success), failed
                        self.translated = "Translation failed!"
                        return
                    }
                }
                guard let results = jsonObj["text"] as? Array<String> else {
                    print("result read fail \n")
                    return
                }
                //set our string variable to the translated text
                self.translated = "\(results[0])"
                //in main thread, update our output field
                DispatchQueue.main.async{
                    self.outputTF.text = self.translated 
                }
            } catch {
                print("Error")
            }
        }
        task.resume()
    }
    
    
    @IBAction func InputLangButtonClicked(_ sender: UIButton) {
        SelectingInput = true
        SelectingOutput = false
        LanguagePicker.isHidden = false
    }
    
    @IBAction func OutputLangButtonClicked(_ sender: UIButton) {
        SelectingInput = false
        SelectingOutput = true
        LanguagePicker.isHidden = false
    }
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    //if we made a selection through the picker, update button text immediately
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if SelectingInput {
            InputLangButton.setTitle("\(Array(mapLangCode.keys)[row])", for: .normal)
        }
        else if SelectingOutput{
            OutputLangButton.setTitle("\(Array(mapLangCode.keys)[row])", for: .normal)
        }
        LanguagePicker.isHidden = true
    }
    
    //how many items will appear in the picker
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return mapLangCode.count
    }
    
    //The data to return for the row and component (column) that's being passed in.
    //Basically returns the language name
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return "\(Array(mapLangCode.keys)[row])"
    }
    
    //dismisses keyboard if user clicks somewhere else
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        super.touchesBegan(touches, with: event)
        let touch = touches.first
        if InputTF.isFirstResponder && touch?.view != InputTF {
            InputTF.resignFirstResponder()
        }
        if outputTF.isFirstResponder && touch?.view != outputTF {
            outputTF.resignFirstResponder()
        }
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        self.view.endEditing(true)
        return false
    }
    
    // MARK: - Navigation
    
    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "DetailSegue"{
            if let DetailVC = segue.destination as? TranslateDetailViewController {
                LanguagePicker.isHidden = true
                //pass the text to show to the next view controller
                DetailVC.textToShow = self.outputTF.text ?? ""
            }
            else {return}
        }
    }
    
}
