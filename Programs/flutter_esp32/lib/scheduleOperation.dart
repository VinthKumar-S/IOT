import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter_esp32/schedules.dart';

Future<void> addSchedule(Schedule schedule) async{
  try{
    await FirebaseFirestore.instance.collection('schedule').add(schedule.toMap());
    print("added");
  }
  catch (e){
    print("Exception");
    print(e);
  }
}