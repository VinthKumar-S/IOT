import 'package:flutter/material.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'package:get/get.dart';

class scheduleDate extends GetxController{
  late FlutterLocalNotificationsPlugin flutterLocalNotificationsPlugin;

  @override
  void onInit() {
    // TODO: implement onInit
    super.onInit();

    flutterLocalNotificationsPlugin = FlutterLocalNotificationsPlugin();

    const AndroidInitializationSettings InitializationSettingsAndroid = AndroidInitializationSettings('@mipmap/ic_launcher');

    final InitializationSettings initializationSettings = InitializationSettings(android: InitializationSettingsAndroid);

    flutterLocalNotificationsPlugin.initialize(
      initializationSettings
    );
  }
}

class scheduleDateState extends StatelessWidget {
  
  final controller = Get.put(scheduleDate());

  final FlutterLocalNotificationsPlugin flutterLocalNotificationsPlugin = FlutterLocalNotificationsPlugin();

  void showNotificationDetails() async{
   const androidPlatformChannelSpecifics = AndroidNotificationDetails("Sprinkeler","Event");

   const NotificationDetails platformChannelsSpecifics = NotificationDetails(android: androidPlatformChannelSpecifics);

   await flutterLocalNotificationsPlugin.show(
    0, 
    'Hello', 
    "This is a simple notificatio", 
    platformChannelsSpecifics,
    payload: 'Notification Payload',
    );
  } 

  @override
  Widget build(BuildContext context) {
    return  Scaffold(
      body: Center(
        child: ElevatedButton(
          onPressed: showNotificationDetails,
          child:Text("Press") ),
      ),
    );
  }
}