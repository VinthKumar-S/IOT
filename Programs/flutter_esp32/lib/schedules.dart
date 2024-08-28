class Schedule {
  String eventName;
  String dates;
  int id;

  Schedule({required this.dates,required this.eventName,required this.id});

  Map<String,dynamic> toMap(){

    return {
      'eventName':eventName,
      'eventDate':dates,
      'id':id
    };
  }

}