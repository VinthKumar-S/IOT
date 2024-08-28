class Schedule {
  String eventName;
  String dates;

  Schedule({required this.dates,required this.eventName});

  Map<String,dynamic> toMap(){
    return {
      'eventName':eventName,
      'eventDate':dates
    };
  }

}