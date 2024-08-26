import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';

class NotificationService{
  final FlutterLocalNotificationsPlugin notificationsPlugin =FlutterLocalNotificationsPlugin();

  Future<void> iniNotification() async{
    AndroidInitializationSettings initializationSettingsAndroid = 
      const AndroidInitializationSettings('');

    var initializationSettings = InitializationSettings(android: initializationSettingsAndroid);

    await notificationsPlugin.initialize(initializationSettings,
      onDidReceiveBackgroundNotificationResponse: (NotificationResponse notificationResponse)async{

      });
  }

  notificationDetails({iconName='calendar'}){
    return const NotificationDetails(
      android:AndroidNotificationDetails('channelId', 'channelName',
      importance: Importance.max,
      icon: '@drawable/calendar',
      color: Colors.purple
      )
    );
  }

  Future showNotification({int id=0, String? title,String? body,String? payLoad,String? icon}) async{
    return notificationsPlugin.show(id, title, body, notificationDetails(iconName:icon));
  }
}