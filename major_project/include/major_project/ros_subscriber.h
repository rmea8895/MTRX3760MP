// header guards...

class CROSSub{
  public:
    CRROSub(ros::NodeHandlePtr nh_);
  private:
    template<typename T> void init(T);
  protected:
    ros::NodeHandlePtr nh_;
    ros::Subscriber subscriber;
};

void CRROSub::init(T, std::string topic){
  subscriber = nh_->subscribe(topic, 10, T, this);
}