import akka.actor.{ActorSystem, Props}

import networking.{IPFSFetcher, IPFSdispatch, NodeActor}

case class TransactionData(data: String)

object Main extends App {

  val system = ActorSystem("BlockchainNetwork")

  val node1 = system.actorOf(NodeActor.props, "node1")
  val node2 = system.actorOf(NodeActor.props, "node2")
  val nodes = Seq(node1, node2)

  val dispatcher = system.actorOf(IPFSdispatch.props(nodes), "dispatcher")

  val ipfsFetcher = system.actorOf(IPFSFetcher.props(dispatcher), "ipfsFetcher")

  val initialHash = "Qmf9z1ya8oDWj16eGPhgXmqcvd3qvBzoYULEzEvjTHkxYD"
  ipfsFetcher ! initialHash
}


