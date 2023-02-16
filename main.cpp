/* EMERGENCY ROOM INTELLIGENT EXPERT DIAGNOSES SYSTEM
 Victor Ekpenyong, Kaleb Perez, Aaron Parks */
#include <iostream> 
#include <vector> // Vector Library
#include <unordered_map> // Unordered Map Library
#include <bits/stdc++.h> // Set precision Library
using namespace std;

                            /*KNOWLEDGE BASE START
---------------------------------------------------------------------------------*/

                              /* BACKWARD CHAINING */

/* Vector which holds the variables coorelated with each rule index. 
Each line represents a rule. NULL is used as an empty holding space since 5 variable spots are given to each rule. */
                          //   1              2          3          4            5
vector<string> clauseVars = {"Headache-Q","SevereV-Q","Cough-Q","Stomach-Q","Dizzy-Q", 
                            "Headache-Q","NULL","NULL","NULL","NULL", 
                            "Headache-Q","SevereV-Q","NULL","NULL","NULL", 
                            "Headache-Q","SevereV-Q","Cough-Q","NULL","NULL",
                            "Headache-Q","SevereV-Q","Cough-Q","Stomach-Q","NULL",
                            "Headache-Q","SevereV-Q","Cough-Q","Stomach-Q","Dizzy-Q",
                            "HEADACHE","Vomiting-Q","NULL","NULL","NULL",
                            "HEADACHE","Vomiting-Q","Nauseous-Q","NULL","NULL",
                            "HEADACHE","Vomiting-Q","Nauseous-Q","NULL","NULL",
                            "VOMITING","Child-Q","NULL","NULL","NULL",
                            "VOMITING","Child-Q","NULL","NULL","NULL",
                            "NAUSEOUS","Seizures-Q","NULL","NULL","NULL",
                            "NAUSEOUS","Seizures-Q","Diarrhea-Q","NULL","NULL",
                            "NAUSEOUS","Seizures-Q","Diarrhea-Q","NULL","NULL",
                            "DIARRHEA","NULL","NULL","NULL","NULL",
                            "SEIZURES","Tremors-Q","NULL","NULL","NULL",
                            "SEIZURES","Tremors-Q","NULL","NULL","NULL",
                            "TREMORS","Hypertension-Q","NULL","NULL","NULL",
                            "TREMORS","Hypertension-Q","NULL","NULL","NULL",
                            "HYPERTENSION","NULL","NULL","NULL","NULL",
                            "DIZZY","Nauseous-Q","NULL","NULL","NULL",
                            "DIZZY","Nauseous-Q","NULL","NULL","NULL",
                            "STOMACH","Appetite-Q","NULL","NULL","NULL",
                            "STOMACH","Appetite-Q","NULL","NULL","NULL",
                            "APPETITE","NULL","NULL","NULL","NULL",
                            "COUGH","Breath-Q","NULL","NULL","NULL",
                            "COUGH","Breath-Q","NULL","NULL","NULL",
                            "BREATH","Gums-Q","NULL","NULL","NULL",
                            "BREATH","Gums-Q","NULL","NULL","NULL",
                            "GUMS","NULL","NULL","NULL","NULL",
                            "SEVERE_V","Throat-Q","NULL","NULL","NULL",
                            "SEVERE_V","Throat-Q","NULL","NULL","NULL",
                            "THROAT","NULL","NULL","NULL","NULL"};

/*Vector which coorelates with clause variables holding their intened results for each rule to be satisfied and bring it's conclusion.
NULL serves as empty holding space*/
vector<string> clauseVarsResults = {"false","false","false","false","false", //10
                            "true","NULL","NULL","NULL","NULL", //20
                            "false","true","NULL","NULL","NULL", //30
                            "false","false","true","NULL","NULL", //40
                            "false","false","false","true","NULL",
                            "false","false","false","false","true",
                            "true","true","NULL","NULL","NULL",
                            "true","false","true","NULL","NULL",
                            "true","false","false","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","true","NULL","NULL",
                            "true","false","false","NULL","NULL",
                            "true","NULL","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","NULL","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","NULL","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","NULL","NULL","NULL","NULL",
                            "true","true","NULL","NULL","NULL",
                            "true","false","NULL","NULL","NULL",
                            "true","NULL","NULL","NULL","NULL"};

/* Map which is used for faster lookups which connect each conclusion variable with its rule number(s) */
unordered_map<string, vector<int>> conclusionList = {{"POISON",{10,90,100,110,140,150,170,190,200,220,240,250,270,290,300,320,330}},
{"HEADACHE",{20}},{"SEVERE_V",{30}},{"COUGH",{40}},{"STOMACH",{50}},{"DIZZY",{60}},{"VOMITING",{70}},{"NAUSEOUS",{80,210}},
{"SEIZURES",{120}},{"DIARRHEA",{130}},{"TREMORS",{160}},{"HYPERTENSION",{180}},{"APPETITE",{230}},{"BREATH",{260}},{"GUMS",{280}},{"THROAT",{310}}};

/* Map which is used for faster lookups and is used to pull the question to prompt the user based on the variable name */
unordered_map<string,string> questions = {{"Headache-Q","Does the patient have a headache?"},{"Vomiting-Q","Is the patient vomiting?"},
{"Child-Q","Is the patient a child?"},{"Nauseous-Q","Is the patient nauseous?"},{"Seizures-Q","Is the patient having seizures?"},
{"Tremors-Q","Is the patient having tremors?"},{"Hypertension-Q","Is the patient having high blood pressure?"},
{"Diarrhea-Q","Is the patient having diarrhea?"},{"SevereV-Q","Is the patient having severe vomiting?"},
{"Cough-Q","Does the patient have a cough?"},{"Stomach-Q","Does the patient have stomach pain?"},{"Dizzy-Q","Is the patient dizzy?"},
{"Appetite-Q","Does the patient have loss of appetite?"},{"Breath-Q","Does the patient have shortness of breath?"},
{"Gums-Q","Does the patient have swollen gums?"},{"Throat-Q","Does the patient have throat pain?"},};

/* Map which is used for faster lookups and is used to see whether a variable within a rule class has been initialized already and with which value(true or false)
NULL is initialized with each map key since at the start of program no information is known*/
unordered_map<string, string> clauseVarsValuesList = {{"Headache-Q","NULL"},{"Vomiting-Q","NULL"},
{"Child-Q","NULL"},{"Nauseous-Q","NULL"},{"Seizures-Q","NULL"},{"Tremors-Q","NULL"},{"Hypertension-Q","NULL"},
{"Diarrhea-Q","NULL"},{"SevereV-Q","NULL"},{"Cough-Q","NULL"},{"Stomach-Q","NULL"},{"Dizzy-Q","NULL"},
{"Appetite-Q","NULL"},{"Breath-Q","NULL"},{"Gums-Q","NULL"},{"Throat-Q","NULL"}};

/* Map which is used for faster lookups and coorelates each rule index with their respective specific conclusion*/
unordered_map<int,string> conclusions = {{10,"Not Sick/No Data"},{20,"HEADACHE"},{30,"SEVERE_V"},{40,"COUGH"},{50,"STOMACH"},{60,"DIZZY"},
{70,"VOMITING"},{80,"NAUSEOUS"},{90,"Lead Poisoning Adult"},{100,"Lead Poisoning Child"},{110,"Carbon Monoxide"},{120,"SEIZURES"},{130,"DIARRHEA"},
{140,"Lead Poisoning Adult"},{150,"Stomach Virus"},{160,"TREMORS"},{170,"Cyanide"},{180,"HYPERTENSION"},{190,"Organic Mercury Inhaled"},
{200,"Hemlock Ingested"},{210,"NAUSEOUS"},{220,"Lead Poisoning Adult"},{230,"APPETITE"},{240,"Ricin Ingested"},{250,"Food Poisoning"},
{260,"BREATH"},{270,"Ricin Inhaled"},{280,"GUMS"},{290,"Nitric Acid Inhaled"},{300,"Elemental Mercury Inhaled"},
{310,"THROAT"},{320,"Death Cap Mushroom"},{330,"Nitric Acid Ingested"}};



                          /* FORWARD CHAINING */

// Vector which holds the variables coorelated with each rule index.
vector<string>forwardClauseVars = {"POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON","POISON"};

/*Vector which coorelates with clause variables holding their intened results for each rule to be satisfied and bring it's conclusion.*/
vector<string>forwardClauseVarsResults = {"Lead Poisoning Child","Carbon Monoxide","Elemental Mercury Inhaled","Organic Mercury Inhaled",
"Cyanide","Stomach Virus","Lead Poisoning Adult","Not Sick/No Data","Ricin Ingested","Food Poisoning","Ricin Inhaled","Nitric Acid Inhaled",
"Nitric Acid Ingested","Hemlock Ingested","Death Cap Mushroom"};

/* Map which is used for faster lookups and coorelates each rule index with their respective specific conclusion*/
unordered_map<int,string> forwardconclusions = {{10,"Chelation therapy with high amounts of lead"},{20,"Breathing pure oxygen and/or time spent in pressurized oxygen chamber"},
{30,"Chelation therapy via fluid through an IV. Oxygen through a face mask. Medicine to treat symptoms. Dialysis, and surgery to remove mercury"},
{40,"Chelation therapy via fluid through an IV. Oxygen through a face mask. Medicine to treat symptoms. Dialysis, and surgery to remove mercury"},
{50,"Give hydroxocobalamin (Cyanokit), sodium thiosulfate and sodium nitrite (Nithiodote)"},{60,"Give Antidiarrheal, Antibiotics, and drink plenty of fluids"},
{70,"EDTA Chelation therapy with high amounts of lead"},{80,"Diagnosis is inconclusive and knowledge base is not able to diagnose patient"},
{90,"Give aggressive intravenous fluid and electrolyte replacement with single dose of activated charcoal"},
{100,"Patient should stay hydrated and drink plenty of fluids. Symptoms will resolve over some days"},
{110,"Give oxygen, and/or mechanical ventilation, with pulmonary hygiene procedure"},
{120,"Give respiratory management, ventilatory support, and steroids"},{130,"Give respiratory management, ventilatory support, and steroids"},
{140,"Give anti-seizure medication, gastral tract decontaminant, and ventilation"},{150,"Prescribe Acetylcysteine"}};

/* Map which is used for faster lookups and is used to see whether a variable within a rule class has been initialized already and with which value(true or false)
NULL is initialized with each map key since at the start of program no information is known*/
unordered_map<string, string> forwardClauseVarsValuesList = {{"POISON", "NULL"}};

/*---------------------------------------------------------------------------------
KNOWLEDGE BASE END*/

// Backwards Chaining Function Prototypes
string backward_chaining_process(string conclusion, int index);
string backward_recursive_conclusion_process(string conclusion, int index);
bool backward_search_conclusion_list(string conclusion, int index);
bool backward_rule_to_clause(int rule_index);
bool backward_validate_clause(int clause_num);
void backward_update_clause_vars_list(int clause_num);
string backward_promptQuestion(string variable);



/*****************************************************************************************************************
* Function which is called to prompt the user a question and return their answer as a string of true or false         
*                    
*                                                                   
*****************************************************************************************************************/
string backward_promptQuestion(string variable) {
    string result;
    cout << endl << questions[variable] << endl;
    cout << "(Y/N)" << endl;
    getline(cin, result);
    if(result == "y" || result == "Y") {
        return "true";
    }
    else if(result == "n" || result == "N") {
      return "false";
    }
    else {
      cout << endl << "Incorrect input, try again." << endl;
      return backward_promptQuestion(variable);
    }
}

  

/*****************************************************************************************************************
* Void function which updates the clauseVarsValuesList by either the additon of a new variable through a       
* recursive call or the upating of an already existing clause variable through prompting the user for the                   
* answer                                                                    
*****************************************************************************************************************/
void backward_update_clause_vars_list(int clause_num) {
    if(!clauseVarsValuesList.count(clauseVars[clause_num])) {
        string unknown = backward_recursive_conclusion_process(clauseVars[clause_num],0);
        clauseVarsValuesList[clauseVars[clause_num]] = unknown;
    }
    else if(clauseVarsValuesList[clauseVars[clause_num]] == "NULL") {
        clauseVarsValuesList[clauseVars[clause_num]] = backward_promptQuestion(clauseVars[clause_num]);
    }
}


/*****************************************************************************************************************
* Bool function which returns true or false whether value in clauseVarsValuesList is equal to the expected         
* value in clauseVars Results                   
*                                                                   
*****************************************************************************************************************/
bool backward_validate_clause(int clause_num) {
    if(clauseVarsValuesList[clauseVars[clause_num]] == clauseVarsResults[clause_num]) {
        return true;
    }
    return false;
}


/*****************************************************************************************************************
* Function which takes the passed in rule index and calculates the start index of the clause number. 
* While loop is used to loop throguh the 5 indexes coorelating to said rule index. If the clause variable is not NULL,
* then update clause vars function is called as well as validate clause. 
* The moment validate clause return false, function return false                                                                                
*****************************************************************************************************************/
bool backward_rule_to_clause(int rule_index) {
    int clause_num = 5 * ((rule_index / 10) - 1);
    int max_clause_index = clause_num + 5;
    bool result = true;
    while(clause_num < max_clause_index) {
        if(clauseVars[clause_num] != "NULL") {
            backward_update_clause_vars_list(clause_num);
            result = backward_validate_clause(clause_num);
        }
        if(result == false) {
            return result;
        }
        clause_num++;
    }
    return result;
}

/*****************************************************************************************************************
* Function takes in conclusion variable name and map vector index and searches map for rule index.
* Rule to Clause function called from here and bool result is returned         
                                                                                      
*****************************************************************************************************************/
bool backward_search_conclusion_list(string conclusion, int index) {
    int rule_index;
    bool poisonFound = false;
    rule_index = conclusionList[conclusion][index];
    poisonFound = backward_rule_to_clause(rule_index);
    return poisonFound;
}

/*****************************************************************************************************************
* Function very similar to backward_chaining_process but used for unknown variables existing
within a rule. Function can be recursive in nature if many variables are unknown. Function return true
or false based on if user input matches intended result

*****************************************************************************************************************/
string backward_recursive_conclusion_process(string conclusion, int index) {
    bool poison_result = false;
    while(index < conclusionList[conclusion].size()) {
        poison_result = backward_search_conclusion_list(conclusion, index);
        if(poison_result == true) {
            return "true";
        }
        index++;
    }
    return "false";
}

/*****************************************************************************************************************
*         Function very similar to recursive_conclusion_process, but is only called once within main.            *
*         This function is the starting point of the backward chaining process which will return the             *
*         poison conclusion back to the main function                                                            *
*****************************************************************************************************************/
string backward_chaining_process(string conclusion, int index) {
    bool poison_result = false;
    while(index < conclusionList[conclusion].size()) {
        poison_result = backward_search_conclusion_list(conclusion, index);
        if(poison_result == true) {
            break;
        }
        index++;
    }
    return conclusions[conclusionList[conclusion][index]];;
}

                          /* Forward Chaining Starts Here */

/* Prototypes Forward Chaining*/
string forward_chaining_process();
bool forward_search_conclusion_list(int index);
bool forward_update_clause_vars_list(string fact);
bool forward_validate_clause(int index, string fact);
int forward_clause_to_rule(int index);
/* End Forward Chaining Prototypes */

/*****************************************************************************************************************
* This function is the starting point of the backward chaining process which will return the poison conclusion back
to the main function  

*****************************************************************************************************************/
string forward_chaining_process() {
  bool fact_check = false;
  int index = 0;
  int forward_rule_index;
  while(index < forwardClauseVars.size()){
    fact_check = forward_search_conclusion_list(index);
    if(fact_check){
      forward_rule_index = forward_clause_to_rule(index);
      break;
    }
    index++;
  }
  return forwardconclusions[forward_rule_index];
}


/*****************************************************************************************************************
* Bool function which returns true or false whether value in forwardClauseVarsValuesList is equal to the expected         
* value in forwardClauseVars Results                   
*                                                                   
*****************************************************************************************************************/
bool forward_validate_clause(int index, string fact) {
  if (forwardClauseVarsResults[index] == forwardClauseVarsValuesList[fact]) {
    return true;
    }
  return false;
}

/*****************************************************************************************************************
* Function takes in index and determines fact we are looking at. Checking process of whether fact exists and 
* validation takes place
                                                                                      
*****************************************************************************************************************/
bool forward_search_conclusion_list(int index) {
  string fact = forwardClauseVars[index];
  bool forward_valid;
  bool fact_exists = forward_update_clause_vars_list(fact);
  if (fact_exists) {
    forward_valid = forward_validate_clause(index,fact);
    if (!forward_valid) {
      return false;
    }
  }
  return true;
}

/*****************************************************************************************************************
* Function checks whether passed in fact exists within forwardClauseVarsValuesList
                                                                                      
*****************************************************************************************************************/
bool forward_update_clause_vars_list(string fact) {
  if (forwardClauseVarsValuesList.count(fact)) {
    return true;
  }
  return false;
}

/*****************************************************************************************************************
* Function converts index of verified fact into rule number of treatment.
                                                                                      
*****************************************************************************************************************/
int forward_clause_to_rule(int index) {
  int rule_index = (index + 1) * 10;
  return rule_index;
}


/*                                       Main starts here               */
/*                       Main prints labels and calls functions for output */
int main() {
  clock_t start, end; // Measure program time
  start = clock(); // Program start
  cout << "WELCOME TO THE EMERGENCY ROOM INTELLIGENT EXPERT DIAGNOSES SYSTEM" << endl << endl;
  cout << "We can diagnose the patient efficiently starting with some questions below" << endl << endl << endl;
  string poison = backward_chaining_process("POISON", 0);
  cout << endl << "CONCLUSION" << endl;
  cout << endl << "Patient has been poisoned by -- " << poison << endl;
  forwardClauseVarsValuesList["POISON"] = poison;
  string treatment = forward_chaining_process();
  cout << endl << "Suggested Treatment -- " << treatment << endl;
  
  /* Gets time it takes for program to run */
  end = clock(); // Program End
  double time_taken = double(end-start) / double(CLOCKS_PER_SEC); // Print time to screen
  cout << endl << "The time taken for this program to run was: " << fixed << time_taken << setprecision(4);
  cout << " seconds." << endl;


}

