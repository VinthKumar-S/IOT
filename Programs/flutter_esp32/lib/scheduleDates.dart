import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_esp32/notificationSerivce.dart';
import 'package:get/get.dart';

// NotificationService().showNotification(title: 'Sample Title',body: 'It Works');

class scheduleDate extends GetxController{

}

class scheduleDateState extends StatelessWidget {
  final controler = Get.put(scheduleDate());
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor:Colors.amber,
      ),
      body: SingleChildScrollView(

      ),
      floatingActionButton: FloatingActionButton(
        backgroundColor: Colors.purple,
        child: Icon(
          Icons.add,
          color: Colors.white,
        ),
        onPressed:(){
          
      }),
    );
  }
}