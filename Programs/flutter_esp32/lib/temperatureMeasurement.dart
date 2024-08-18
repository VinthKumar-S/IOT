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
      ),
      body: Center(
        child: Obx((){
          double temperature=controller._temperature.value;
          double humidity=controller._humidity.value;
          return Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text('$temperature'),
              Text('$humidity')
            ],
          );
        })
      ),
    );
  }
}