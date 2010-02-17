<?php

class FeedsODKParser extends FeedsParser {
  /**
   * Implement FeedsParser::parse().
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    if (!class_exists('FeedsODKBatch') || !($batch instanceof FeedsODKBatch)) {
      throw Exception(t('ODK Parser needs to be paired with ODK Fetcher'));
    }
    $parsed = $this->parseXML($batch->getRaw());
    feeds_odk_log($parsed);
    $batch->setItems(array($parsed));
  }

  /**
   * Parse the submitted XML.
   */
  protected function parseXML($raw) {
    $raw = <<<EOF
<?xml version='1.0' ?>
    <geotagger id="geo_tagger">
      <DeviceId>A0000015B6FF70</DeviceId>
      <Image>1266373610389.jpg</Image>
      <Location>38.91677205 -77.03591701666667 45.6 12.0</Location>
      <Description>DS office</Description>
    </geotagger>
EOF;
    $xml = @ new SimpleXMLElement($raw);
    list($lat, $lon, $alt, $acc) = explode(' ', (string) @current($xml->xpath('/geotagger/Location')));
    return array(
      'device_id' => (string) @current($xml->xpath('/geotagger/DeviceId')),
      'image' => (string) @current($xml->xpath('/geotagger/Image')),
      'latitude' => $lat,
      'longitude' => $lon,
      'altitude' => $alt,
      'accuracy' => $acc,
      'description' => (string) @current($xml->xpath('/geotagger/Description')),
      );
  }
}