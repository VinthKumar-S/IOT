import 'package:flutter_local_notifications/flutter_local_notifications.dart';

class NotificationService{
  final FlutterLocalNotificationsPlugin notificationsPlugin =FlutterLocalNotificationsPlugin();

  Future<void> iniNotification() async{
    AndroidInitializationSettings initializationSettingsAndroid = 
      const AndroidInitializationSettings('calendar');

    var initializationSettings = InitializationSettings(android: initializationSettingsAndroid);

    await notificationsPlugin.initialize(initializationSettings,
      onDidReceiveBackgroundNotificationResponse: (NotificationResponse notificationResponse)async{

      });
  }

  notificationDetails(){
    return const NotificationDetails(
      android:AndroidNotificationDetails('channelId', 'channelName',
      importance: Importance.max)
    );
  }

  Future showNotification({int id=0, String? title,String? body,String? payLoad}) async{
    return notificationsPlugin.show(id, title, body, notificationDetails());
  }
}