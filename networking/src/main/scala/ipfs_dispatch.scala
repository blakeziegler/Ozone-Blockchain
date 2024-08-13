package networking
import java.util.Properties
import akka.actor._
import akka.actor.{Actor, Props}
import akka.stream._
import akka.stream.scaladsl._
import networking.TransactionData

class IPFSdispatch(nodes: Seq[ActorRef]) extends Actor {
  def receive: Receive = {
    case TransactionData(data) =>
      nodes.foreach(_ ! TransactionData(data)) // transmit data to all nodes

    case _ => println("Message Unknown")
  }
}

object IPFSdispatch{
  def props(nodes: Seq[ActorRef]): Props =
    Props(new IPFSdispatch(nodes))
}
