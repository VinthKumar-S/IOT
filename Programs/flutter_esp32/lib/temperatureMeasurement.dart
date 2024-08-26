
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:get/get.dart';

class temperatureMeasure extends GetxController{
  var _humidity = 0.0.obs;
  var _temperature=0.0.obs;
  
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

  String getWeatherImage(){
    if(_humidity.value>80){
      return 'asserts/rainy-removebg-preview.png';
    }
    else if(_temperature.value >30){
      return 'asserts/sunny-removebg-preview.png';
    }
    else{
      return 'asserts/Cloud-removebg-preview.png';
    }
  }
}

class temperatureMeasureState extends StatelessWidget {
  temperatureMeasureState({super.key});
  final temperatureMeasure controller = Get.put(temperatureMeasure());

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          backgroundColor: Colors.purple,
          title: Text(
            "TEMPERATURE",
            style: TextStyle(
              fontWeight: FontWeight.bold,
              color: Colors.white
            ),
            ),

        ),
      body:Obx((){
          double temperature=controller._temperature.value;
          double humidity=controller._humidity.value;

          return Column(
            mainAxisAlignment: MainAxisAlignment.start,
            children: [
              //Text('$temperature'),
              //Text('$humidity')
                Container(
                  width: 500,
                  height: 200,
                  child: Center(
                    child: AnimatedSwitcher(
                      duration: Duration(seconds: 10),
                      transitionBuilder: (Widget child,Animation<double> animation){
                        return FadeTransition(opacity: animation,child: child,);
                      },
                      child: Image.asset(
                        controller.getWeatherImage(),
                        width: 200,
                        height: 200,
                      ),
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