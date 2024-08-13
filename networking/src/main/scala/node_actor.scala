package networking
import akka.actor.{ Actor, Props }
import akka.actor.{Actor, Props}
import akka.stream._
import akka.stream.scaladsl._


// unpacking data at node: 
class NodeActor extends Actor {
  def receive: Receive = {
    case TransactionData(data) =>
      println(s"Node ${self.path.name} received block data: $data")
    case _ => println("Unknown message received")
  }
}

object NodeActor {
  def props: Props = Props(new NodeActor)
}
