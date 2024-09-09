import 'package:flutter_esp32/notificationSerivce.dart';
import 'package:get/get.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:intl/intl.dart';

class NotficationController extends GetxController{
  var datesList = <DocumentSnapshot>[].obs;

  @override
  void onInit() {
    // TODO: implement onInit
    super.onInit();
    fetchDate();
  }

  void fetchDate() async {
    try{
      var result = await FirebaseFirestore.instance.collection("schedule").get();
      datesList.value = result.docs;
      checkForNotification();
    }
    catch(e){
      Get.snackbar('Error', e.toString());
    }
  }

  void checkForNotification(){
    var now = DateTime.now();
    String today = DateFormat('yyyy-MM-dd').format(now);
    String currentTime = DateFormat('HH:mm:ss').format(now);

    for(var date in datesList){
      String firestoreDate = date['eventDate'];
      String firestoreTime = date['eventTime'];

      if(firestoreDate ==  today && firestoreTime == currentTime ){
        NotificationService().showNotification(title: 'Sprinkler',body: date['eventName']);
      }

    }
  }
}