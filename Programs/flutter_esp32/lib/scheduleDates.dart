
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_esp32/scheduleObj.dart';
import 'package:get/get.dart';
import 'scheduleOperation.dart';
import 'package:intl/intl.dart';

// NotificationService().showNotification(title: 'Sample Title',body: 'It Works');

class scheduleDate extends GetxController{
  
  var dataList =<DocumentSnapshot>[].obs;
  var selectedDate = ''.obs;

  void onInit() async{
    // TODO: implement onInit 
    super.onInit();
    fetchData();
  }


  void fetchData() async{
    try{
      var result = await FirebaseFirestore.instance.collection('schedule').get();
      dataList.value = result.docs;
      //print(dataList.length);
    }
    catch(e){
      Get.snackbar("Error",e.toString());
    }
  }

  void updateDate(String date) {
    selectedDate.value = date;
   // print(date);
  }


}

bool isSameDate(DateTime date1,DateTime date2){
  return DateFormat('yyyy-MM-dd').format(date1)== DateFormat('yyyy-MM-dd').format(date2);
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
                  shadowColor: Colors.white,
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
                    subtitle: Text(data['eventDate'].toString().substring(0,10).split('-').reversed.join('-')),
                    trailing: IconButton(
                      icon: Icon(Icons.remove),
                      onPressed: ()async{
                        await deleteDate(data.id);
                        controler.fetchData();
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
                Obx((){ 
                    var date ="".obs;
                    if(controler.selectedDate.value.length != 0){
                      date.value = controler.selectedDate.value.substring(0,10).split('-').reversed.join('-');
                    }
                    return TextFormField(
                      readOnly: true,
                      controller: TextEditingController(
                        text: date.value
                      ),
                      onTap: () => _selectDate(context),
                      decoration: InputDecoration(
                        labelText: 'Date',
                        border: OutlineInputBorder()
                      ),
                    );
                 })
              ],
            ),
            textConfirm: "Add",
            textCancel: "Cancel",
            onConfirm: () async{
              String scheduleName = controller1.text;
              String date = controller2.text;
              Get.back();
              controller1.clear();
              controller2.clear();

              Schedule schedule= Schedule(dates: controler.selectedDate.value, eventName: scheduleName);
              await addSchedule(schedule);
              controler.fetchData();
            },
         );
      }),
    );
  }

  _selectDate(BuildContext context) async{
    DateTime initialDate = DateTime.now();
    DateTime? pickedDate = await showDatePicker(
      context: context,
      initialDate: initialDate, 
      firstDate: DateTime(2020), 
      lastDate: DateTime(2030));

      if (pickedDate != null){
        String formattedDate = DateFormat("yyyy-MM-dd'T'HH:mm:ss'Z'").format(pickedDate);
        controler.updateDate(formattedDate);
      }
  }
}