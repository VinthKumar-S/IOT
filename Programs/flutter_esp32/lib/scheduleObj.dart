import 'package:get/get_connect/http/src/utils/utils.dart';

class Schedule {
  String eventName;
  String dates;
  String time;

  Schedule({required this.dates,required this.eventName,required this.time});

  Map<String,dynamic> toMap(){

    return {
      'eventName':eventName,
      'eventDate':dates,
      'eventTime':time,
    };
  }

}