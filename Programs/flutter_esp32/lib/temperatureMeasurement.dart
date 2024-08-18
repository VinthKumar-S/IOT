import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:get/get.dart';

class temperatureMeasure extends GetxController{
  var _humidity = 0.0.obs;
  var _temperature=0.0.obs;
  
  FirebaseDatabase database = FirebaseDatabase.instance;

  final firebaseApp = Firebase.app();

  DatabaseReference ref = FirebaseDatabase.instance.ref();
  
  @override
  void onInit() {
    // TODO: implement onInit
    super.onInit();
    readData();
  }

  void readData() async{
    ref.onValue.listen((event) {
      final data = event.snapshot.value as Map<dynamic, dynamic>;
      _temperature.value = double.parse(data['Temperature']!);
    });

    ref.onValue.listen((event) {
      final data = event.snapshot.value as Map<dynamic, dynamic>;
      _humidity.value = double.parse(data['Humidity']!);
    });
  }
}

class temperatureMeasureState extends StatelessWidget {
  temperatureMeasureState({super.key});
  final temperatureMeasure controller = Get.put(temperatureMeasure());

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Weather Condition'),
        backgroundColor: Colors.amber,
      ),
      body:Obx((){
          double temperature=controller._temperature.value;
          double humidity=controller._humidity.value;
          String weatherCondition ="No Rain";
          if(humidity>85){
            weatherCondition="Heavy rain will occure";
          }
          return Column(
            mainAxisAlignment: MainAxisAlignment.start,
            children: [
              //Text('$temperature'),
              //Text('$humidity')
                Container(
                  width: 500,
                  height: 150,
                  child: Center(
                   /* child: Text(
                      weatherCondition,
                      style: TextStyle(
                        color: Colors.white,
                        fontSize: 30,
                        fontWeight: FontWeight.bold
                      ),
                    ),*/
                    child: Icon(
                      Icons.wb_sunny,
                      size: 130,
                      color: Colors.white,
                    ),
                  ),
                  decoration: BoxDecoration
                  (
                    color: Colors.purple,
                    borderRadius: BorderRadius.only(
                      bottomLeft: Radius.circular(40),
                      bottomRight: Radius.circular(40)
                    ),
                    boxShadow:[
                      new BoxShadow(
                        color: Colors.black,
                        blurRadius: 15.0
                      )
                    ]
                  ),
                ),
                SizedBox(height:150),
                Table(
                 // border: TableBorder.all(color: Colors.black),
                 columnWidths: {
                    0:FixedColumnWidth(200.0),
                    1:FlexColumnWidth(),
                    2:FixedColumnWidth(250.0)
                 },
                  children: [
                    TableRow(
                      decoration: BoxDecoration(
                        //color: Colors.grey[300]
                      ),
                      children:[
                          Column(
                            children: [
                              Text(
                                "Temperature",
                                style: TextStyle(
                                  fontWeight: FontWeight.bold,
                                  fontSize: 23
                                ),
                              )
                            ],
                          ),
                           Column(
                            children: [
                              Text(
                                "Humidity",
                                style: TextStyle(
                                  fontWeight: FontWeight.bold,
                                  fontSize: 23
                                ),
                              )
                            ],
                          ),
                      ] 
                    ),
                    TableRow(
                      decoration: BoxDecoration(
                        //color: Colors.grey[300]
                      ),
                      children:[
                          Column(
                            children: [
                              SizedBox(height: 20,),
                              Text(
                                "$temperature",
                                style: TextStyle(
                                  fontSize: 22
                                ),
                              )
                            ],
                          ),
                           Column(
                            children: [
                              SizedBox(height: 20,),
                              Text(
                                "$humidity",
                                style: TextStyle(
                                  fontSize: 22
                                ),
                              )
                            ],
                          ),
                      ] 
                    )
                  ],
                )
            ],
          );
        })
    );
  }
}