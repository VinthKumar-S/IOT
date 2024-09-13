import 'package:cron/cron.dart';
import 'package:flutter_esp32/notificationSerivce.dart';


class CronJobService{
  final cron = Cron();
  final NotificationService notificationService = NotificationService();
  void scheduledTaskDateTime(DateTime dateTime){
    final durationUntilSchedule = dateTime.difference(DateTime.now());

    cron.schedule(Schedule.parse('*/1 * * * *'), () async{
      if(DateTime.now().isAfter(dateTime)){
        notificationService.showNotification(
          title: "Test",body:"Success"
        );
      }
    });
  print('Scheduled task will run in $durationUntilSchedule'); 
  }
}