package networking

import akka.actor.{Actor, ActorRef, Props}
import akka.stream.Materializer
import akka.util.ByteString
import scala.concurrent.ExecutionContext
import scala.concurrent.Future
import akka.dispatch.sysmsg.SystemMessage
import org.slf4j.Logger
import scalaj.http._

case class TransactionData(data: String)

// Define the IPFSFetcher actor
class IPFSFetcher(dispatcher: ActorRef) extends Actor {
  def receive: Receive = {
    case hash: String =>
      println(s"Fetching data from IPFS with hash: $hash") 
      val url = s"http://127.0.0.1:8080/ipfs/$hash" // grab data from url w/ hash
      val response: HttpResponse[String] = Http(url).asString // http response -> string
      if (response.is2xx) {
        println(s"Data successfully fetched from IPFS: ${response.body}")
        dispatcher ! TransactionData(response.body)
      } else {
        println(s"Failed to fetch data from IPFS. Status code: ${response.code}")
      }

    case _ => println("Unknown message received")
  }
}

object IPFSFetcher {
  def props(dispatcher: ActorRef): Props = Props(new IPFSFetcher(dispatcher))
}


