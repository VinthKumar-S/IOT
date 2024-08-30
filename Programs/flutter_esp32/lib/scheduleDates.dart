import 'dart:math';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_esp32/notificationSerivce.dart';
import 'package:flutter_esp32/schedules.dart';
import 'package:get/get.dart';
import 'scheduleOperation.dart';

// NotificationService().showNotification(title: 'Sample Title',body: 'It Works');

class scheduleDate extends GetxController{

  DatabaseReference ref = FirebaseDatabase.instance.ref("Schedules");
  
  var dataList =<DocumentSnapshot>[].obs;

  void onInit() async{
    // TODO: implement onInit 
    super.onInit();
    fetchData();
  }

  void addSchedule(name,date)async{

    final Random _random = Random();

    var randomNumber = 0.obs;

    randomNumber.value =_random.nextInt(100);

    await ref.set({
      randomNumber.value:{
        "name":name,
        "date":date,
      }
    });
  }

  void fetchData() async{
    try{
      var result = await FirebaseFirestore.instance.collection('schedule').get();
      dataList.value = result.docs;
      print(dataList.length);
    }
    catch(e){
      Get.snackbar("Error",e.toString());
    }
  }
}

class scheduleDateState extends StatelessWidget {
  final controler = Get.put(scheduleDate());
  final TextEditingController controller1 = TextEditingController();
  final TextEditingController controller2 = TextEditingController();
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor:Colors.purple,
        title: Text(
          'SCHEDULE DATE',
            style: TextStyle(
              fontWeight: FontWeight.bold,
              color: Colors.white
            ),
        ),
      ),
      body: Obx((){
          return ListView.builder(
            shrinkWrap: true,
            itemCount: controler.dataList.length,
            itemBuilder:(context,index){  
                var data= controler.dataList[index];
                return Card(
                  color: Colors.white,
                  elevation: 10,
                  child: ListTile(
                    leading: Text(
                      '$index',
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 20.0
                      ),
                    ),
                    title: Text(
                      data['eventName']
                      ,style: TextStyle(
                        fontStyle: FontStyle.italic,
                        fontSize: 18.0
                      ),
                      ),
                    subtitle: Text(data['eventDate']),
                    trailing: IconButton(
                      icon: Icon(Icons.remove),
                      onPressed: (){
                        
                      },  
                    ),
                  ),
                );
            });
      }),
      floatingActionButton: FloatingActionButton(
        backgroundColor: Colors.purple,
        child: Icon(
          Icons.add,
          color: Colors.white,
        ),
        onPressed:(){
         // NotificationService().showNotification(title: 'Sample Title',body: 'It Works');
         Get.defaultDialog(
            title: "Add Date",
            content: Column(
              children: [
                TextFormField(
                  controller: controller1,
                  decoration: InputDecoration(
                    labelText: 'Schedule Name',
                    border: OutlineInputBorder()
                  ),
                ),
                SizedBox(height: 10,),
                TextFormField(
                  controller: controller2,
                  decoration: InputDecoration(
                    labelText: 'Date',
                    border: OutlineInputBorder()
                  ),
                )
              ],
            ),
            textConfirm: "Add",
            textCancel: "Cancel",
            onConfirm: () async{
              String scheduleName = controller1.text;
              String date = controller2.text;
              Get.back();
              controler.addSchedule(scheduleName, date);
              controller1.clear();
              controller2.clear();

              Schedule schedule= Schedule(dates: date, eventName: scheduleName);
              await addSchedule(schedule);
              controler.fetchData();
            }
         );
      }),
    );
  }
}