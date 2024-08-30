import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter_esp32/scheduleObj.dart';

Future<void> addSchedule(Schedule schedule) async{
  try{
    await FirebaseFirestore.instance.collection('schedule').add(schedule.toMap());
  }
  catch (e){
    print(e);
  }
}

Future<void> deleteDate(String scheduleId)async {
    await FirebaseFirestore.instance.collection('schedule').doc(scheduleId).delete();
}